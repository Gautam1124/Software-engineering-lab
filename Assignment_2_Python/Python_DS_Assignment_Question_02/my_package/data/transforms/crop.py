# Imports
from PIL import Image
import random


class CropImage(object):
    '''
        Performs either random cropping or center cropping.
    '''
    __slots__ = "_wid", "_hgt", "_type"

    def __init__(self, shape, crop_type='center'):
        self._wid, self._hgt = shape
        self._type = crop_type

    def __call__(self, image):
       if self._type == 'center':
          left = (image.width - self._wid)/2
          top = (image.height - self._hgt)/2
          right = (image.width + self._wid)/2
          bottom = (image.height + self._hgt)/2

       else :
          left = 0
          top = 0
          right = self._wid
          bottom = self._hgt
       im1 = image.crop(left,top,right,bottom)
       return im1
