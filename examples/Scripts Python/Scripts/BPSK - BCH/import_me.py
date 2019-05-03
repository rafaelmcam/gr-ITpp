# -*- coding: utf-8 -*-
import numpy as np
import cv2
import os


def readOutput(path, mini_preamble, header, img_shape):
    with open(path, "rb") as f:
        b = f.read()
    rcv = np.frombuffer(b, dtype = np.uint8)
    
    bit_shift = getBitShift(rcv, mini_preamble)
    rcv2 = np.packbits(np.roll(np.unpackbits(rcv), bit_shift))
    info = getBeginMiniPacket(rcv2, mini_preamble)
    rcv_array = findHeader(info, header)
    rgb = rcvArray2BMP(rcv_array, img_shape)
    return rgb

def rcvArray2BMP(rcv_array, shape):
    bgr = np.flipud(rcv_array[122:].reshape(shape[0], shape[1], 3))
    rgb = cv2.cvtColor(bgr, cv2.COLOR_BGR2RGB)
    return rgb

def findHeader(info, header):
    pos = np.argmax(np.correlate(np.unpackbits(info), np.unpackbits(header)))
    rcv_array = np.packbits(np.roll(np.unpackbits(info), -pos))
    return rcv_array
    

def getBitShift(rcv, mini_preamble):
    result = 0
    for bit_shift in range(8):
        aux = np.packbits(np.roll(np.unpackbits(rcv), bit_shift))
        if len(search_sequence_numpy(aux, mini_preamble)) > result:
            result = bit_shift
    return result

def getBeginMiniPacket(rcv2, mini_preamble):
    ref, result = len(rcv2), 0
    for shiftByte in range(2 + 2): #tamanho do minipacket (ex: 2 de informação e 2 de preamble no stream MUX no gnuradio)
        aux = np.roll(rcv2, shiftByte)
        aux = np.array([x for i, x in enumerate(aux) if i % 4 >= 2])
        _ = len(search_sequence_numpy(aux, mini_preamble))
        if _ < ref:
            ref = _
            result = shiftByte
    return np.array([x for i, x in enumerate(np.roll(rcv2, result)) if i % 4 >= 2])

#######
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