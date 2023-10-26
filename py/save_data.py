import numpy as np
import re
from scipy.io import wavfile
import os

def saveData(loadDataPath, saveDataPath, fs):
    X = []

    with open(loadDataPath, 'r') as file:
        content = file.read()

    pattern = r'COMPONENT #\d+\s*\[(.*?)\]'
    matches = re.findall(pattern, content)

    for match in matches:
        values = [float(x) for x in match.split(', ')]
        X.append(values)
    X = np.array(X, dtype=np.float32)
    for i in range(X.shape[0]):
        wavfile.write(os.path.join(saveDataPath, 'ica') + str(str(i).zfill(2)) + ".wav", fs, X[i,:])

saveData('../logs/algo output/output.txt','../data/sources/', 8000)