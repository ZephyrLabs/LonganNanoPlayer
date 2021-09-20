# LonganNanoPlayer
 A simple project that plays a video on the LCD of the Sipeed Longan nano with SPI library using DMA 

clone this repository and compile with platformio installed and setup for the Longan Nano board (GDV32)
___

### how to play video ?
after flashing the firmware.hex/bin to your device, 
use a TF card formatted to fat/fat32/exfat format and place the logo.bin and bmp.bin files, 
in the root directory.

insert the card in the TF slot located on the underside of the board, and power on to see the video being played.

### how to create custom video/bmp.bin

The custom bin file is produced by taking the raw binary data from uncompressed images and stitching them together, and
quickly changing the image in concession to make it appear like a video (like old age film players)

you first need all the images of individual frames of the video you would like to play.

this can be created using `ffmpeg`

the corresponding command being:
`ffmpeg -i (replace/with/video/path/../.mp4) -s 160x80 -pix_fmt rgb24 thumb%04d.bmp -hide_banner`

note the number of frames generated by this process

To create a custom bin file you can utilise the [genhex.py](http://dl.sipeed.com/LONGAN/Nano/Firmware/badapple_demo_tools/tools_bmp2hex.zip) tool provided by sipeed themseleves.

Edit genhex.py and change this line to:
`os.system("python bmp2hex.py -kbin thumb{0:04}.bmp".format(num))`

replace the word `bmp2hex.py` with the path to the bmp2hex.py file and place the 3 python scripts in the same folder as the video (note down this path).
you can now modify that line above again to:
`os.system("python path/to/files/../bmp2hex.py -kbin path/to/files/../thumb{0:04}.bmp".format(num))`

in the same genhex.py script, 
modify this line:
`while num <= 5640:`
change the number to whatever number of frames you got from ffmpeg.

you will also need to change the line in src/main.cpp
` for (int i=0; i<5640;i++)`
and change the number here as well.
recompile and reflash.

after running the genhex.py script, the bmp.bin file will mostly be located in the root folder of the system you ran this on.

replace this file on the TF card and run!

### how to create custom logo.bin
take any 160x80 image you wish to use as your logo, and run it through [binary converter tool online](https://www.lvgl.io/tools/imageconverter) make sure the output name is logo.bin, and format as RGB565 (no swap)

