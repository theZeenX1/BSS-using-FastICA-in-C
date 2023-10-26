import numpy as np
from scipy.io import wavfile
import os
import struct

def loadData(dataPath, outputPath, nsources=9):
    # Create the output folder if it doesn't exist
    os.makedirs(dataPath, exist_ok=True)

    for i in range(nsources):
        fs, data = wavfile.read(os.path.join(dataPath, 'mix') + str(str(i).zfill(2)) + '.wav')
        data = data.astype(np.float64)
        data = data.tolist()
        # Generate the output file name
        output_file = os.path.join(outputPath, f"input{i:02}.txt")

        # Save the data to the binary file
        with open(output_file, 'wb') as binary_file:
            binary_file.write(len(data).to_bytes(4, "little"))
            for dat in data:
                binary_file.write(struct.pack('<d', dat))

loadData('../data/mix/', '../logs/py output', 9)
