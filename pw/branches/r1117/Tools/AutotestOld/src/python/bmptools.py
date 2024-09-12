import struct
import logging
import numarray

def readBmp(filename):
  '''
    Read a .BMP file

    filename --- file to read

    Attention: function can read XRGB8 files only
  '''
  f = file(filename, 'rb')

  fBITMAPFILEHEADER = '=HIHHI'
  # Skip BITMAPFILEHEADER as we don't use any information from it
  f.seek(struct.calcsize(fBITMAPFILEHEADER), 1)

  fBITMAPINFOHEADER = '=IllHHIIllII'
  bitmapinfoheader = f.read(struct.calcsize(fBITMAPINFOHEADER))

  (
    _,
    width, height,
    planes, bitCount,
    compression, _, _, _, _, _
  ) =  struct.unpack(fBITMAPINFOHEADER, bitmapinfoheader)
  assert planes == 1, 'cannot read this BMP'
  assert compression == 0, 'cannot read this BMP'

  actualHeight = height
  if height < 0:
    actualHeight = -height

  bytesPerPixel = bitCount / 8;

  a = numarray.fromfile(f, numarray.UInt8, (actualHeight, width, bytesPerPixel))

  if height < 0:
    return a[::-1]
  else:
    return a

class PixelNorms(object):
  '''
    Placeholder for pixel norms

    All the norms recieves three arrays of positive RGB components as
    an input and returns calculated norm

    Attention: for performance reasons norms can reuse any of passed arrays
  '''

  @staticmethod
  def maximum(dr, dg, db):
    '''
      Maximum-of-components norm
    '''
    numarray.maximum(dr, dg, dr)
    numarray.maximum(dr, db, dr)
    return dr

  @staticmethod
  def sum(dr, dg, db):
    '''
      Sum-of-components norm
    '''
    dr += dg
    dr += db
    return dr

def countOnes(a):
  '''
    Return number of 1 in an array
  '''
  return numarray.sum(a.flat, type = numarray.Long)

def rgb(img):
  '''
    Return a tuple of components array
  '''
  return img[:,:,2], img[:,:,1], img[:,:,0]

def background((r, g, b), (bgR, bgG, bgB)):
  '''
    Return an array of the same shape with 1 where color is BG and 0 otherwise
  '''
  return (r == bgR) & (g == bgG) & (b == bgB)

def normed(norm, img0, img1):
  '''
    Calculate pixel norm for images' difference

    norm --- pixel norm to apply
    img0, img1 --- images to compare
  '''
  diff = numarray.array(img0, type = numarray.Int16)
  numarray.subtract(diff, img1, diff)
  numarray.abs(diff, diff)
  return norm(*rgb(diff))

class Norm(object):
  '''
    Base class for image norms
  '''
  def __init__(self, comparator):
    '''
      Ctor

      comparator --- comparator to apply to images
    '''
    self.comparator_ = comparator

  def __call__(self, img0, img1):
    return self.comparator_(img0, img1)

class CountingNorm(Norm):
  '''
    Counting norm

    TODO: Documentation
  '''
  def __init__(self, pixelNorm, threshold, bgColor):
    def comparator(img0, img1):
      bg = background(rgb(img0), bgColor) & background(rgb(img1), bgColor)
      notBgSize = bg.size() - countOnes(bg)

      clipped = numarray.greater(normed(pixelNorm, img0, img1), threshold)

      eps = float(countOnes(clipped))/notBgSize
      logging.debug('counting norm: eps = %.5f', eps)
      return eps

    Norm.__init__(self, comparator)

  name = 'counting norm'

class AvgNorm(Norm):
  '''
    Average norm

    TODO: Documentation
  '''
  def __init__(self, pixelNorm):
    def comparator(img0, img1):
      eps = normed(pixelNorm, img0, img1).mean()
      logging.debug('average norm: eps = %.5f', eps)
      return eps

    Norm.__init__(self, comparator)

  name = 'average norm'
