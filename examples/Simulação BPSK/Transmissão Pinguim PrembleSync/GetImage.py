import numpy as np
import matplotlib.pyplot as plt
import cv2


with open("../Transmissão RedDot Usando ConstellationMod/penguin.bmp", "rb")as f:
    _ = f.read()
    orig = np.frombuffer(_, dtype=np.uint8)

preamble = orig[:122]

with open("output_preamble_sync.data", "rb")as f:
    _ = f.read()

rcv = np.frombuffer(_, dtype=np.uint8)


def search_sequence_numpy(arr, seq):
    # Store sizes of input array and sequence
    Na, Nseq = arr.size, seq.size

    # Range of sequence
    r_seq = np.arange(Nseq)

    # Create a 2D array of sliding indices across the entire length of input array.
    # Match up with the input sequence & get the matching starting indices.
    M = (arr[np.arange(Na - Nseq + 1)[:, None] + r_seq] == seq).all(1)

    # Get the range of those indices as final output
    if M.any() > 0:
        return np.where(np.convolve(M, np.ones((Nseq), dtype=int)) > 0)[0]
    else:
        return []         # No match found


def findBitShift_and_Begin2(rcv_bitmap):
    for i in range(8):
        aux = search_sequence_numpy(np.packbits(np.roll(np.unpackbits(rcv_bitmap), i)), np.array([66, 77, 138]))
        if len(aux) != 0:
            return (i, aux[0])


def FindHeader(rcv, preamble):
    tup = findBitShift_and_Begin2(rcv)
    if tup is not None:
        print("Preamble Found")
        img = np.roll(np.packbits(np.roll(np.unpackbits(rcv), tup[0])), -tup[1])
    else:
        print("Preamble not Found, using correlation... Takes much longer")
        array = np.unpackbits(rcv)
        preambleU = np.unpackbits(preamble)
        xcorr = np.correlate(array, preambleU)
        img = np.packbits(np.roll(array, -np.argmax(xcorr)))
    img = img[122:].reshape((450, 600, 3))
    final = np.flipud(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    return final


finalImg = FindHeader(rcv, preamble)

plt.figure(figsize=(12, 12))
plt.axis("off")
plt.imshow(finalImg)


# Also save image in bmp format
pl = preamble.tolist()
bmpReverse = np.flipud(cv2.cvtColor(finalImg, cv2.COLOR_RGB2BGR))
imgl = bmpReverse.ravel().tolist()
bmpFinal = np.array(pl + imgl, dtype=np.uint8)

with open("forceBmp.bmp", "wb")as f:
    f.write(bmpFinal)

print("Image written to 'forceBmp.bmp'")

origBit = np.unpackbits(orig[122:])
finalBit = np.unpackbits(bmpFinal[122:])

print("BER: ", 1 - np.mean(np.equal(origBit, finalBit)))

#  plt.show()
