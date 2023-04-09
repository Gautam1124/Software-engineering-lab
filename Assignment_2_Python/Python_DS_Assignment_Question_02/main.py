
from my_package.model import ImageCaptioningModel
from my_package.data import Dataset, Download
from my_package.data.transforms import FlipImage, RescaleImage, BlurImage, CropImage, RotateImage
import numpy as np
import os
from PIL import Image


def experiment(annotation_file, captioner, transforms, outputs):
    '''
        Function to perform the desired experiments

        Arguments:
        annotation_file: Path to annotation file
        captioner: The image captioner
        transforms: List of transformation classes
        outputs: Path of the output folder to store the images
    '''

    #Create the instances of the dataset, download
    data = Dataset(annotation_file,transforms)
    down = Download()

    #Print image names and their captions from annotation file using dataset object
    for i in range(len(data)):
        image = data.__getann__(i)
        image_name = image["file_name"]
        image_caption = image["captions"]
        print("Image Name:", image_name)
        for iter_cnt,caption in enumerate(image_caption):
            print(str(iter_cnt) + '-' + caption["caption"])
        print('\n\n')

    #Download images to ./data/imgs/ folder using download object
    cwd = os.getcwd()
    for i in range(len(data)):
        image = data.__getann__(i)
        image_name = image["file_name"]
        image_url = image["url"]
        down(cwd + "/data/imgs/" + image_name, image_url)


    #Transform the required image (3.jpg) and save it seperately
        #save the transformed image
    image = Image.open(cwd + "/data/imgs/0.jpg")
    outputs = cwd + "/Outputs"

    image1 = image
    image_pth = outputs + "/" + "original.jpg"
    image1.save(image_pth)
    caption = captioner(np.array(image1),3)
    print("For:: Original image")
    for it in caption:
        print(it)
    print('\n\n')
    
    for index, t in enumerate(transforms):
        image1 = t(image)
        image_filename = t.__class__.__name__ + "_"+ str(index) + ".jpg"
        image_path = outputs + "/" + image_filename
        image1.save(image_path)
        caption = captioner(np.array(image1),3)
        print("For:: ",t.__class__.__name__)
        for it in caption:
            print(it)
        print('\n\n')

def main():
    captioner = ImageCaptioningModel()
    experiment('./data/annotations.jsonl', captioner, [FlipImage(), BlurImage(1),RotateImage(-90),RotateImage(45),RescaleImage(0.5),RescaleImage(2)], None) # Sample arguments to call experiment()


if __name__ == '__main__':
    main()
