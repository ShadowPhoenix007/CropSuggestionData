import os
from sklearn.tree import DecisionTreeClassifier, plot_tree
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn import svm
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
import keras
import seaborn
import joblib

seaborn.set_theme()

path = "C:/Users/ASUS/Downloads/ImagineCupTest/CropSuggestionData/CropReco.csv"

ard = pd.read_csv(path)
numClasses = ard['label'].unique().shape[0]
classes = ard['label'].unique()

print("Number of classes = ", numClasses)
print("Classes = ", classes)

grouped = ard.groupby("label")

columns = ['N', 'P', 'K', 'temperature', 'humidity', 'ph', 'rainfall', 'label']

features = ard[columns]
dataNPK = ard[["N", "P", "K"]]
features.pop("N")
features.pop("P")
features.pop("K")

trainX, testX, trainY, testY = train_test_split(features, dataNPK, test_size=0.3, random_state=69)

# def evaluate(model):
#     predictions = model.predict(testX)
#     acc = accuracy_score(predictions, testY)
#     return round(acc*100)

model = DecisionTreeClassifier(criterion='gini', max_depth = 12, random_state = 69)
model.fit(trainX,trainY)

# acc = evaluate(model)
# print(f"Accuracy = {acc}%")

sample = np.array([[29.49096726, 60, 8, 153.2504506, 15]])
print (model.predict(sample))

joblib.dump(model, "agromodel2.sav") 