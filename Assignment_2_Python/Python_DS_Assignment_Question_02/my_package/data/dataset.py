#Imports
import json
import jsonlines
from PIL import Image
import os
import numpy as np

class Dataset(object):
    '''
        A class for the dataset that will return data items as per the given index
    '''

    def __init__(self, annotation_file, transforms=None):
        '''
            Arguments:
            annotation_file: path to the annotation file
            transforms: list of transforms (class instances)
                        For instance, [<class 'RandomCrop'>, <class 'Rotate'>]
        '''
        self.transforms = transforms
        with open(annotation_file,'r+') as annoFile:
            annoList = list(annoFile)
        self.annoList = []
        for annostr in annoList:
          self.annoList.append(json.loads(annostr))
     

    def __len__(self):
        '''
            return the number of data points in the dataset
        '''
        return len(self.annoList)

    
    def __getann__(self, idx):
        '''
            return the data items for the index idx as an object
        '''
        return self.annoList[idx]
       
        

    def __transformitem__(self, path):
        '''
            return transformed PIL Image object for the image in the given path
        '''
        if self.transforms != None:
            img_trans = Image.open(path)
            for transform in self.transforms:
                image  = transform(image)
                print(f"performed Transition : {transform}")
        return img_trans
        
            
