import joblib
import numpy as np
# load
loadedModel = joblib.load("agromodel.sav")
sample = np.array([[21, 74, 60, 29.49096726, 20, 6.471862118, 153.2504506]])
print(loadedModel.predict(sample))

loadedModel = joblib.load("agromodel2.sav")
sample2 = np.array([[21, 74, 60, 29.49096726, 20, 6.471862118, 153.2504506]])
print(loadedModel.predict(sample2))