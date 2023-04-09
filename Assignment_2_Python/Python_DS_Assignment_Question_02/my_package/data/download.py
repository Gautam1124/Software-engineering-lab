from PIL import Image
import requests
from io import BytesIO

class Download(object):
    '''
        A class for helping in dowloading the required images from the given url to the specified path
    '''

    def __call__(self, path, url):
        '''
            Arguments:
            path: download path with the file name
            url: required image URL
        '''
        response = requests.get(url)
        img = BytesIO(response.content)
        with open(path,"wb") as f:
            f.write(img.getvalue())

if __name__ == "__main__":
    temp = Download()
    temp("./out/02.jpg","https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQXI3Y7egNYB7cLm9noR2Gxhy6ewX3Tz0erotSz_Xil&s")
