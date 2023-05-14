import os
import sys
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

path = os.path.join(sys.path[0], "Crop_recommendation.csv")

ard = pd.read_csv(path)
numClasses = ard['label'].unique().shape[0]
classes = ard['label'].unique()

print("Number of classes = ", numClasses)
print("Classes = ", classes)

ard.describe()

grouped = ard.groupby("label")

columns = ['N', 'P', 'K', 'temperature', 'humidity', 'ph', 'rainfall']

features = ard[columns]
labels = ard[["label"]]
train_X, test_X, train_y, test_y = train_test_split(features, labels, test_size=0.3, random_state=69, stratify=labels)

model = DecisionTreeClassifier(criterion='gini', max_depth = 12, random_state = 69)
model.fit(train_X,train_y)

def evaluate(model):
    predictions = model.predict(test_X)
    acc = accuracy_score(predictions, test_y)
    return round(acc*100, 3)

acc = evaluate(model)
print(f"Accuracy = {acc}%")

rice_sample = np.array([[21, 74, 19, 29.49096726, 20, 6.471862118, 153.2504506]])
print (model.predict(rice_sample))

joblib.dump(model, "agromodel.sav") 


"""fig, axy = plt.subplots(4, 2, figsize=(9, 16))
axy[0, 0].set_title("Nitrogen")
grouped.mean()["N"].plot(kind="barh", ax=axy[0, 0])
axy[0, 1].set_title("Phosphorus")
grouped.mean()["P"].plot(kind="barh", ax=axy[0, 1])
axy[1, 0].set_title("Potassium")
grouped.mean()["K"].plot(kind="barh", ax=axy[1, 0])
axy[1, 1].set_title("Temperature")
grouped.mean()["temperature"].plot(kind="barh", ax=axy[1, 1])
axy[2, 0].set_title("Humidity")
grouped.mean()["humidity"].plot(kind="barh", ax=axy[2, 0])
axy[2, 1].set_title("Rainfall")
grouped.mean()["rainfall"].plot(kind="barh", ax=axy[2, 1])
axy[3, 0].set_title("pH value")
grouped.mean()["ph"].plot(kind="barh", ax=axy[3, 0])
plt.tight_layout()
plt.show()"""