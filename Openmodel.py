#To run this, you must first run the model creation program, which uses joblib to dump a model into the source folder
#This is just a sample program to show the working of the two models

import joblib
import numpy as np
# load
loadedModel = joblib.load("agromodel.sav")
sample = np.array([[60, 55, 44, 23.00445915, 82.3207629, 7.840207144, 263.9642476]])
print(loadedModel.predict(sample))

loadedModel2 = joblib.load("agromodel2.sav")
sample2 = np.array([[23.00445915, 82.3207629, 7.840207144, 263.9642476, 0]])
print(loadedModel2.predict(sample2))