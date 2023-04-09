# Imports
from PIL import Image, ImageFilter


class BlurImage(object):
      '''
        Applies Gaussian Blur on the image.
      '''
      __slots__ = '_radius'
      def __init__(self, radius):
          self._radius = radius

      def __call__(self, image):
          im1 = image.filter(ImageFilter.GaussianBlur(self._radius))
          return im1
