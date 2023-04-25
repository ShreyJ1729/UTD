from matplotlib import pyplot as plt
import numpy as np
from PIL import Image

def is_pixel_transparent(pixel):
    return (pixel == [0, 0, 0, 0]).all()

def crop_and_resample_run(gif, i):
    gif.seek(i)

    # get the frame as numpy array
    frame = gif.convert("RGBA")
    frame = np.array(frame)

    # remove top 90, bottom 90, left 110, right 100 pixels
    frame = frame[105:-90, 110:-100]

    # resample the frame to 60x70
    frame = Image.fromarray(frame)
    frame = frame.resize((40, 50), Image.LANCZOS)
    frame = np.array(frame)

    return frame


def crop_and_resample_idle(gif, i):
    gif.seek(i)

    # get the frame as numpy array
    frame = gif.convert("RGBA")
    frame = np.array(frame)

    # resample the frame to 30x50
    frame = Image.fromarray(frame)
    frame = frame.resize((30, 50), Image.LANCZOS)
    frame = np.array(frame)

    return frame

def get_memory_mario(frame, frame_number, flip=True):
    height, width, channels = frame.shape
    if flip:
        frame = np.fliplr(frame)
    memory = []
    for y in range(height):
        for x in range(width):
            pixel = frame[y, x]
            if is_pixel_transparent(pixel):
                continue
            hex_value = (
                "0x00" + "".join(["{:02x}".format(c) for c in pixel[:3]]).upper()
            )
            memory.append((x, y, hex_value))
    
    return memory

def get_memory_clear_mario(frame):
    height, width, channels = frame.shape
    memory = []
    for y in range(height):
        for x in range(width):
            hex_value = "0x00000000"
            memory.append((x, y, hex_value)) 
    return memory

if __name__ == "__main__":
    maxx = 0
    maxy = 0

    gif = Image.open("mario-run.gif")
    num_frames = gif.n_frames
    run_memory = {"left": [], "right": []}
    for i in range(num_frames):
        frame = crop_and_resample_run(gif, i)
        frame[frame[:, :, 3] < 200] = [0, 0, 0, 0]
        run_memory["right"].append(get_memory_mario(frame, frame_number=i))
        run_memory["left"].append(get_memory_mario(frame, frame_number=i, flip=True))



    gif = Image.open("mario-idle.gif")
    num_frames = gif.n_frames
    idle_memory = {"left": [], "right": []}
    for i in range(num_frames):
        frame = crop_and_resample_idle(gif, i)
        frame[frame[:, :, 3] < 200] = [0, 0, 0, 0]
        idle_memory["right"].append(get_memory_mario(frame, frame_number=i))
        idle_memory["left"].append(get_memory_mario(frame, frame_number=i, flip=True))
    
    frame = crop_and_resample_idle(gif, 0)
    clear_memory = get_memory_clear_mario(frame)
    
    # now write the memory to a file
    with open("mario-memory.asm", "w") as f:
        for direction in run_memory:
            for i, frame in enumerate(run_memory[direction]):
                f.write(f"mario_run_{direction}_frame_{i}: .word ")
                for x, y, hex_value in frame:
                    f.write(f"{x}, {y}, {hex_value}, ")
                f.write("0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF\n")

        for direction in idle_memory:
            for i, frame in enumerate(idle_memory[direction]):
                f.write(f"mario_idle_{direction}_frame_{i}: .word ")
                for x, y, hex_value in frame:
                    f.write(f"{x}, {y}, {hex_value}, ")
                f.write("0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF\n")
        
        f.write(f"mario_clear_frame: .word ")
        frame = clear_memory
        for x, y, hex_value in frame:
            f.write(f"{x}, {y}, {hex_value}, ")
        f.write("0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF\n")
    
    print(maxx, maxy)