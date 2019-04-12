import numpy as np
import os

def readSave(readfileName, savefileName = "output.bmp", delete = False):
    with open(readfileName, "rb") as f:
        b = f.read()
    rcv = np.frombuffer(b, dtype = np.uint8)
    r = saveRcvImage(savefileName, rcv)
    if delete == True:
        os.remove(readfileName)
    return r

def saveRcvImage(fileName, rcv):
    tupla = findBitShift_and_Begin(rcv)
    gravar = np.roll(np.packbits(np.roll(np.unpackbits(rcv), tupla[0])), -tupla[1])
    with open(fileName, "wb") as f:
        f.write(gravar)
    return gravar


def findBitShift_and_Begin(rcv_bitmap):
    for i in range(8):
        aux = search_sequence_numpy(np.packbits(np.roll(np.unpackbits(rcv_bitmap), i)), np.array([66, 77]))
        if len(aux) != 0:
            return (i, aux[0])

def search_sequence_numpy(arr,seq):
    """ Find sequence in an array using NumPy only.

    Parameters
    ----------    
    arr    : input 1D array
    seq    : input 1D array

    Output
    ------    
    Output : 1D Array of indices in the input array that satisfy the 
    matching of input sequence in the input array.
    In case of no match, an empty list is returned.
    """

    # Store sizes of input array and sequence
    Na, Nseq = arr.size, seq.size

    # Range of sequence
    r_seq = np.arange(Nseq)

    # Create a 2D array of sliding indices across the entire length of input array.
    # Match up with the input sequence & get the matching starting indices.
    M = (arr[np.arange(Na-Nseq+1)[:,None] + r_seq] == seq).all(1)

    # Get the range of those indices as final output
    if M.any() >0:
        return np.where(np.convolve(M,np.ones((Nseq),dtype=int))>0)[0]
    else:
        return []         # No match found