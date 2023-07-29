#!/bin/bash
# Creating an auto-build bash script.
	# 1. Create a directory in your build directory.
	# 2. Create your bash-script.sh to add the upcoming code.
	# 3. build your bash script using a command --> code bash-script.sh
	# 4. Run your bash script --> ./bash-script.sh
# Pre-scripting.
	# cat meta-mylayer/recipes-core/images/your-image-name.bb
	# Make sure that you've included the next line.
		# IMAGE_FSTYPES = "rpi-sdimg"
            # why? Because we need the image in the format *-sdimg not *.wic. You just need this line because meta-raspberrypi already created a recipe named
            # rpi-sdimg.bb so once we include this line, bitbake runs this recipe that creates what we need (check that it's in the same directory of the *.wic). Now,
            # our *-sdimg is ready to be installed on our sdcard.
            # NB: We're using the -sdimg that have *.rootfs* in its format. Why? Because the one without this extension is just a symbolic link (pointer) pointing to
            # the one with the extension.
	# Let's go now to our script (script is written with the explanation of every single command).
# Scripting.
	IMAGE_FILE_TYPE="sdimg"		# That's what we were talking about.
    IMAGE_DIRECTORY="/home/hussam/poky/build2/tmp/deploy/images/raspberrypi4-64"   # Remove this path and add yours.
    # NB: "" is used to type a string, while '' is used to type a command, and ${any-name} is used to identify any declared variable in bash.
	IMAGE_TO_FLASH=`ls ${IMAGE_DIRECTORY} | grep ${IMAGE_FILE_TYPE} | head -n 1`
        # We know that our *.sdimg is in the path specified in IMAGE_DIRECTORY, so grep on it (go to this directory type ls | grep sdimg if you want to make sure).
		# Just to check: Type the command we've assigned to IMAGE_TO_FLASH in the terminal (it returns the file). Why did we used head -n 1? Because we doesn't want the
        # symbolic link, and when we type ls ${IMAGE_DIRECTORY} | grep sdimg, we'll find that the SL is the second option, so head -n num means bring from the head
        # of the given command, the first num options (et2kd bardo en 3ndk el pointer beytl3 tany wa7d msh awel wa7d el e7na msh 3ayzino).
	# select what you want to do (When we run the bash, we'll have these 2 options in the terminal to choose one of them). You've to erase first then flash.
    select use_option in erase flash
	do
		case ${use_option} in
			erase)
                # Identify the user that you've started the erasing operation.
				echo "Erasing..."
				# Unmount your memory card in the next 2 lines. In windows, unmounting is automated, but in linux we've to unmount manually from memory before erasing.
				sudo umount /dev/sdb1
				sudo umount /dev/sdb2
            
                    # What're mmcblk0p1/p2? Type in the terminal ls /dev/mmcb* --> You'll find 3 partitions (memory blocks), 0/0p1/0p2. Ok, what shall we erase? Open
                    # the disk manager (as if your're erasing manually) and press on each block. Under the block, you'll see the word Device that gives you information
                    # about the location of this block. The first block is already a free size and stored in block0 (/dev/mmcblk0), but the rest is what we need to
                    # erase. Notice that hese 3 blocks are not 3, they are only 1 block but divided into partitions (0 (original)/partition1/partition2).
                    # Do you want to make sure that unmount has been done successfully and nothing is erased? Remove all the next code in the erase) case and run the
                    # bash script then press 1 to choose the first option. Go to the disk manager, and you'll find partitions 1 and 2 still not erased, but how to know
                    # that unmount is done successfully? The last row under Device is named contents, for nor it has no link as before and contains the word not mounted.
                    # Do you want to mount again without completly erasing and flashing from scratch? Press on the button play located on the left above Size.
                # Start erasing the unmounted memory block.
                time sudo dd if=/dev/zero of=/dev/sdb bs=10000 count=1000
                    # NB: We erased the memory block 0, not mmcblk0 and mmcblk0p1 and mmcblk0p2 because as we said before, p1 and p2 are just partitions. So now we can
                    # conclude that the command unmount takes partitions, but of= takes the whole block (et2kd ennaha maynf3sh ta5od partitions kda, bs azon 3ady).
                    # dd is a tool on linux that has the ability to write on a memory card, sdcard, files or even cdrom. Type dd --help in the terminal to get all info.
                    # if= is what i want to input, and of= is what i want to output this input in. So /dev/zero is a built-in all zeros block or file (empty location).
                    # bs= is the block size, so i'm telling him to get from the input a 5GB size and direct it to the output. Why did we use 5GB? Any number > the image
                    # you want to erase is ok, so go to the disk manager and make sure that the size of p1 and p2 is < 5GB, and you'll find that this's satisfied. Then
                    # why don't we use 100GB? Because if we have an extremly large image, don't waste time to look for its size (tab3an da barra 3annena, e7na kda kda
                    # el image bta3tna so8yra fsh5) for not to waste a massive time in erasing. 5GB is ok (azon momken t5liha 1GB aw 22l kaman) (msh mot2kd mn kol da).
                    # count=1000 (msh fahemha awy) is the filteration. I'm telling him do this in number of times = 1000 (azon ma3naha enno y3ml el process dy 1000 marra
                    # 3shan yt2kd enha et3mlt s7).
                    # time is used to return at the end the time of execution of the command in the same line.
                break
                    # In bash, you can use break to skip the loop, or exit(0) to skip the whole file. In our current bash, both are ok.
            ;;
            flash)
                echo "Flashing..."
                # We've just changed the input file from the zeros file to our *-sdimg we want to flash. So now the input is image-file-path/select-it
                time sudo dd if=${IMAGE_DIRECTORY}/${IMAGE_TO_FLASH} of=/dev/sdb bs=1M iflag=fullblock
                # Azon en shar7 el count=1000 kan sa7 3shan hna msh hanst5dmha, fa akid da m3nah en el erasing is not reliable bs el flashing heyya marra bs.
                # bs=300 azon momken tkbrha 3ady, heyya dy bt2ollak 3awz tflash kam Mb fy kol marra, fa law el file size 476 kda hat-flash 3ala marten. Tab leh asln
                # a8yrha? Leh makbrhash w a3mel flash 3ala marra bs? (msh mot2kd bs azon) 3shan el file da el mafrood matfta7oosh fy kol flash, enta tflash w5las msh
                # m7tag ttcheck ay 7aga, fa law el image el adima kant 2000 msln wenta e5trt en bs=2000, w el image el gdida ba2et 2100, kda hayflash 3ala marten, bs
                # kol marra el execution time fel marten hayb2a aknk btflash 2000, fa kda time wasted kteer awy. Fa a7sn 7aga t5liha rqm msh kbeer, 200 msln aw 7aga.
                # Lamma t5ls flashing, 3awzk t2olly howwa bey-create partition lkol bs walla homma 2 bs zy el manual (azon hayb2o 2 bs bardo).
                break
            ;;
            # This is the same as default in c.
            *)
                echo "Invalid input! Press 1 to erase or 2 to flash"
            ;;
            esac
    done
