#Imports
from PIL import Image,ImageOps

class FlipImage(object):
    '''
        Flips the image.
    '''
    __slots__ = "_prop","_imageR"
    def __init__(self, flip_type='horizontal'):
        '''
            Arguments:
            flip_type: 'horizontal' or 'vertical' Default: 'horizontal'
        '''
        self._prop = flip_type

    def __call__(self, image):
        '''
            Arguments:
            image (numpy array or PIL image)
            Returns:
            image (numpy array or PIL image)
        '''
        try :
            if self._prop == 'horizontal':
                img = ImageOps.flip(image)
                return img
            elif self._prop == 'vertical':
                img = ImageOps.mirror(image)
                return img
            else:
                print('Invalid flip_type')
        except:
            print('could not find library')