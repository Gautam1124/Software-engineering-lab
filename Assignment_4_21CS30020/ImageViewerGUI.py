from my_package.model import ImageCaptioningModel
from my_package.model import ImageClassificationModel
from tkinter import *
from functools import partial
from PIL import ImageTk, Image
from tkinter import filedialog
import os


image_name = ""
def fileClick(clicked):
    # Define the function you want to call when the filebrowser button (Open) is clicked.
    # This function should pop-up a dialog for the user to select an input image file.
    # To have a better clarity, please check out the sample video.
    global image_name
    image_name = filedialog.askopenfilename(title='Open image',initialdir='./data/imgs/',filetypes=[('jpg images','*.jpg')])
    
    if(len(image_name)==0):
        print("No file selected");
        return

    Enter.delete(0,END)
    Enter.insert(0,'Image: '+image_name[-5:])

    cwd = os.getcwd()
    image_dir = os.path.join(cwd, 'data', 'imgs')
    image_path = os.path.join(image_dir, image_name)
    image_location = os.path.abspath(image_path)
    
    global main_image
    main_image = Image.open(image_location)
    new_size = (500,500)
    main_image = main_image.resize(new_size)
    main_image = ImageTk.PhotoImage(main_image)
    img_label = Label(root,image=main_image)
    img_label.grid(row=1,column=0,columnspan=3)


def process(clicked, captioner, classifier):
    # This function will produce the required output when 'Process' button is clicked.
    # Note: This should handle the case if the user clicks on the `Process` button without selecting any image file.
    if(len(image_name)==0):
        print("Select the file first")
        return

    # print(image_name)
    if(clicked.get()=="Captioner"):
        caption_list = captioner(image_name)
        caption_list.insert(0,"Top 3 captions are:")
        caption_str_list = []
        for s in caption_list:
            length = len(s)
            spaces = (100 - length)//2
            caption_str_list.append(" "*spaces + s + " "*spaces + '\n')


        label.config(text="\n".join(caption_str_list), relief="solid", borderwidth=1, padx=10, pady=10)
        label.grid(row=1,column=4,columnspan=2)
        #     caption_text.insert('end'," "*spaces + s + " "*spaces + '\n')
        # caption_text.grid(row=1,column=4)

    elif(clicked.get()=="Classification"):
        class_list =   classifier(image_name)
        class_str = []
        for tup in class_list:
            class_str.append(str(tup[1] + "-" + str(round(tup[0]*100,5)) + "%") )
        class_str.insert(0,"Top 3 classes are:")    
        # class_text = Text(root,width=30,height=10,borderwidth=2,relief='solid')
        class_str_list = []
        for s in class_str:
            length = len(s)
            spaces = (100 - length)//2
            class_str_list.append(" "*spaces + s + " "*spaces + '\n')
        label.config(text="\n".join(class_str_list), relief="solid", borderwidth=1, padx=10, pady=10)
        label.grid(row=1,column=4,columnspan=2)
    


if __name__ == '__main__':
    # Complete the main function preferably in this order:
    # Instantiate the root window.
    # Provide a title to the root window.
    # Instantiate the captioner, classifier models.
    # Declare the file browsing button.
    # Declare the drop-down button.
    # Declare the process button.
    # Declare the output label.
    root = Tk()
    root.title("Sw_Assign4_21CS30020")
    caption = ImageCaptioningModel()
    classy =  ImageClassificationModel()
    Enter = Entry(root,borderwidth=5,width=60)
    # global caption_text
    # caption_text = Text(root,width=30,height=10,borderwidth=2,relief='solid')
    label = Label(root,text=' ')
    Enter.grid(row=0,column=0)
    options = ["Captioner","Classification"]
    clicked = StringVar()
    clicked.set(options[0])
    dropdown = OptionMenu(root,clicked, *options)
    dropdown.grid(row=0,column=2)
    button_open = Button(root,text="Open",padx=5,command=partial(fileClick,clicked))
    button_open.grid(row=0,column=1)

    button_process = Button(root,text='Process',padx=5,command=partial(process,clicked,caption,classy)) 
    button_process.grid(row=0,column=3)

    root.mainloop()
