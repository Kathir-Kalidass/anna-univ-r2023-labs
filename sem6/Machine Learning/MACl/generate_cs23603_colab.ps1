$ErrorActionPreference = "Stop"

$root = Join-Path (Get-Location) "CS23603_ML_Colab"
New-Item -ItemType Directory -Path $root -Force | Out-Null

function Convert-ToSourceArray {
    param([string]$Text)

    if ($null -eq $Text) {
        return @()
    }

    $normalized = $Text -replace "`r", ""
    return ($normalized -split "`n") | ForEach-Object { "$_`n" }
}

function New-MarkdownCell {
    param([string]$Text)

    return @{
        cell_type = "markdown"
        metadata = @{ language = "markdown" }
        source = Convert-ToSourceArray -Text $Text
    }
}

function New-CodeCell {
    param([string]$Code)

    return @{
        cell_type = "code"
        metadata = @{ language = "python" }
        execution_count = $null
        outputs = @()
        source = Convert-ToSourceArray -Text $Code
    }
}

function Write-Notebook {
    param([hashtable]$Spec)

    $path = Join-Path $root $Spec.Path
    $dir = Split-Path -Parent $path
    New-Item -ItemType Directory -Path $dir -Force | Out-Null

    $intro = @"
# $($Spec.Title)

## Objective
$($Spec.Objective)

## Google Colab Steps
1. Run the setup cell.
2. Execute the main cell.
3. Save a copy to your Google Drive if needed.
"@

    if ($Spec.Notes) {
        $intro += "`n## Notes`n$($Spec.Notes)`n"
    }

    $cells = @()
    $cells += New-MarkdownCell -Text $intro
    if ($Spec.SetupCode) {
        $cells += New-CodeCell -Code $Spec.SetupCode
    }
    $cells += New-CodeCell -Code $Spec.MainCode

    $notebook = @{
        cells = $cells
        metadata = @{
            colab = @{
                name = [System.IO.Path]::GetFileName($path)
                provenance = @()
            }
            kernelspec = @{
                display_name = "Python 3"
                name = "python3"
            }
            language_info = @{
                name = "python"
            }
        }
        nbformat = 4
        nbformat_minor = 5
    }

    $json = $notebook | ConvertTo-Json -Depth 100
    Set-Content -Path $path -Value $json -Encoding utf8
}

$setupML = "!pip -q install numpy pandas matplotlib seaborn scikit-learn scipy"
$setupCNN = "!pip -q install numpy pandas matplotlib seaborn scikit-learn tensorflow"

$notebooks = @()

function Add-Spec {
    param(
        [string]$Path,
        [string]$Title,
        [string]$Objective,
        [string]$MainCode,
        [string]$SetupCode = "",
        [string]$Notes = ""
    )

    if (-not $SetupCode) {
        $SetupCode = $setupML
    }

    $script:notebooks += @{
        Path = $Path
        Title = $Title
        Objective = $Objective
        MainCode = $MainCode
        SetupCode = $SetupCode
        Notes = $Notes
    }
}

# Unit I - Introduction
Add-Spec -Path "UNIT_1_INTRODUCTION/01_tools_overview_colab_equivalent.ipynb" -Title "Unit I Lab 1: ML Tools Workflow (Colab Equivalent)" -Objective "Understand the ML workflow that tools like WEKA, KNIME, and RapidMiner automate." -MainCode @'
import pandas as pd
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score

iris = load_iris(as_frame=True)
df = iris.frame
display(df.head())

X = df.drop(columns=["target"])
y = df["target"]

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

model = DecisionTreeClassifier(random_state=42)
model.fit(X_train, y_train)
pred = model.predict(X_test)

print("Pipeline: Load -> Split -> Train -> Predict -> Evaluate")
print("Accuracy:", accuracy_score(y_test, pred))
'@ -Notes "GUI tools are not available inside Colab, so this notebook reproduces the same workflow in Python."

Add-Spec -Path "UNIT_1_INTRODUCTION/02_benchmark_dataset_repositories.ipynb" -Title "Unit I Lab 2: Exploring Benchmark Dataset Repositories" -Objective "Explore common benchmark dataset sources and inspect sample benchmark datasets." -MainCode @'
from sklearn.datasets import load_iris, load_wine, fetch_openml

repositories = {
    "UCI ML Repository": "https://archive.ics.uci.edu/ml/index.php",
    "Kaggle Datasets": "https://www.kaggle.com/datasets",
    "OpenML": "https://www.openml.org/",
}

print("Benchmark repositories:")
for name, url in repositories.items():
    print(f"- {name}: {url}")

iris = load_iris(as_frame=True)
wine = load_wine(as_frame=True)

print("\nBuilt-in benchmark snapshots:")
print("Iris shape:", iris.data.shape, "Target classes:", iris.target.nunique())
print("Wine shape:", wine.data.shape, "Target classes:", wine.target.nunique())

try:
    adult = fetch_openml(name="adult", version=2, as_frame=True, parser="auto")
    print("OpenML Adult shape:", adult.data.shape)
except Exception as exc:
    print("OpenML fetch skipped due to runtime/network issue:", exc)
'@

Add-Spec -Path "UNIT_1_INTRODUCTION/03_python_libraries_data_preprocessing_visualization.ipynb" -Title "Unit I Lab 3: Python Libraries for ML" -Objective "Use NumPy, Pandas, Matplotlib, Seaborn, and Scikit-learn for data handling, preprocessing, and visualization." -MainCode @'
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.datasets import load_breast_cancer
from sklearn.preprocessing import StandardScaler

data = load_breast_cancer(as_frame=True)
df = data.frame.copy()
display(df.head())

print("Data descriptive analysis:")
display(df.describe())

X = df.drop(columns=["target"])
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)
print("Scaled matrix shape:", X_scaled.shape)

plt.figure(figsize=(7, 4))
sns.histplot(df["mean radius"], bins=20, kde=True)
plt.title("Distribution: mean radius")
plt.show()

plt.figure(figsize=(8, 6))
subset_corr = df.iloc[:, :8].corr()
sns.heatmap(subset_corr, cmap="coolwarm", annot=False)
plt.title("Correlation heatmap (first 8 features)")
plt.show()
'@

# Unit II - Supervised Learning
Add-Spec -Path "UNIT_2_SUPERVISED/Linear_Regression/linear_regression_synthetic.ipynb" -Title "Linear Regression on Synthetic Data" -Objective "Train and visualize a simple linear regression model on synthetically generated data." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

np.random.seed(42)
X = 2 * np.random.rand(120, 1)
y = 4 + 3 * X[:, 0] + np.random.randn(120)

model = LinearRegression()
model.fit(X, y)
pred = model.predict(X)

plt.figure(figsize=(7, 4))
plt.scatter(X, y, alpha=0.7, label="Actual")
plt.plot(X, pred, color="red", label="Regression line")
plt.xlabel("X")
plt.ylabel("y")
plt.title("Linear Regression - Synthetic Data")
plt.legend()
plt.show()

print("Intercept:", model.intercept_)
print("Slope:", model.coef_[0])
print("MSE:", mean_squared_error(y, pred))
print("R2:", r2_score(y, pred))
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Linear_Regression/linear_regression_csv_upload.ipynb" -Title "Linear Regression on CSV Upload" -Objective "Train simple linear regression from an uploaded CSV file in Colab." -MainCode @'
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from google.colab import files
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

uploaded = files.upload()
file_name = next(iter(uploaded))
df = pd.read_csv(file_name)
display(df.head())

numeric_df = df.select_dtypes(include=np.number).dropna()
if numeric_df.shape[1] < 2:
    raise ValueError("Need at least two numeric columns for simple linear regression.")

feature_col = numeric_df.columns[0]
target_col = numeric_df.columns[-1]

X = numeric_df[[feature_col]]
y = numeric_df[target_col]

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

model = LinearRegression()
model.fit(X_train, y_train)
pred = model.predict(X_test)

print("Feature:", feature_col)
print("Target:", target_col)
print("MAE:", mean_absolute_error(y_test, pred))
print("MSE:", mean_squared_error(y_test, pred))
print("R2:", r2_score(y_test, pred))

plt.figure(figsize=(7, 4))
plt.scatter(y_test, pred, alpha=0.7)
plt.xlabel("Actual")
plt.ylabel("Predicted")
plt.title("Actual vs Predicted")
plt.show()
'@ -Notes "The notebook uses the first numeric column as feature and last numeric column as target."

Add-Spec -Path "UNIT_2_SUPERVISED/Linear_Regression/linear_regression_builtin_diabetes.ipynb" -Title "Linear Regression on Built-in Diabetes Dataset" -Objective "Train simple linear regression using scikit-learn built-in Diabetes data." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_diabetes
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

data = load_diabetes(as_frame=True)
df = data.frame

feature_col = "bmi"
X = df[[feature_col]]
y = df["target"]

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

model = LinearRegression()
model.fit(X_train, y_train)
pred = model.predict(X_test)

x_vals = X_test[feature_col].to_numpy()
order = x_vals.argsort()

plt.figure(figsize=(7, 4))
plt.scatter(x_vals, y_test, alpha=0.7, label="Actual")
plt.plot(x_vals[order], pred[order], color="red", label="Prediction")
plt.xlabel(feature_col)
plt.ylabel("target")
plt.title("Diabetes: Simple Linear Regression")
plt.legend()
plt.show()

print("MAE:", mean_absolute_error(y_test, pred))
print("MSE:", mean_squared_error(y_test, pred))
print("R2:", r2_score(y_test, pred))
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Multiple_Regression/multiple_regression_synthetic.ipynb" -Title "Multiple Linear Regression on Synthetic Data" -Objective "Train multiple linear regression with multiple synthetic input features." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

np.random.seed(42)
X = np.random.rand(200, 3)
y = 2 + 1.5 * X[:, 0] + 3.0 * X[:, 1] - 2.0 * X[:, 2] + np.random.randn(200) * 0.2

model = LinearRegression()
model.fit(X, y)
pred = model.predict(X)

print("Intercept:", model.intercept_)
print("Coefficients:", model.coef_)
print("MSE:", mean_squared_error(y, pred))
print("R2:", r2_score(y, pred))

fig = plt.figure(figsize=(7, 5))
ax = fig.add_subplot(111, projection="3d")
ax.scatter(X[:, 0], X[:, 1], y, alpha=0.6)
ax.set_xlabel("X1")
ax.set_ylabel("X2")
ax.set_zlabel("y")
ax.set_title("Synthetic Multiple Regression (X1, X2, y)")
plt.show()
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Multiple_Regression/multiple_regression_csv_upload.ipynb" -Title "Multiple Regression on CSV Upload" -Objective "Train multiple linear regression using all available features from uploaded CSV." -MainCode @'
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from google.colab import files
from sklearn.model_selection import train_test_split
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.impute import SimpleImputer
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

uploaded = files.upload()
file_name = next(iter(uploaded))
df = pd.read_csv(file_name)
display(df.head())

target_col = df.columns[-1]
X = df.drop(columns=[target_col])
y = pd.to_numeric(df[target_col], errors="coerce")

valid = y.notna()
X = X.loc[valid]
y = y.loc[valid]

num_cols = X.select_dtypes(include=np.number).columns
cat_cols = X.select_dtypes(exclude=np.number).columns

numeric_pipe = Pipeline([
    ("imputer", SimpleImputer(strategy="median")),
    ("scaler", StandardScaler()),
])

categorical_pipe = Pipeline([
    ("imputer", SimpleImputer(strategy="most_frequent")),
    ("onehot", OneHotEncoder(handle_unknown="ignore")),
])

preprocess = ColumnTransformer([
    ("num", numeric_pipe, num_cols),
    ("cat", categorical_pipe, cat_cols),
])

model = Pipeline([
    ("preprocess", preprocess),
    ("regressor", LinearRegression()),
])

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

model.fit(X_train, y_train)
pred = model.predict(X_test)

print("MAE:", mean_absolute_error(y_test, pred))
print("MSE:", mean_squared_error(y_test, pred))
print("R2:", r2_score(y_test, pred))

plt.figure(figsize=(7, 4))
plt.scatter(y_test, pred, alpha=0.7)
plt.xlabel("Actual")
plt.ylabel("Predicted")
plt.title("Multiple Regression: Actual vs Predicted")
plt.show()
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Multiple_Regression/multiple_regression_builtin_california.ipynb" -Title "Multiple Regression on Built-in Dataset" -Objective "Train multiple regression on California Housing (fallback to Diabetes if download fails)." -MainCode @'
import matplotlib.pyplot as plt
from sklearn.datasets import fetch_california_housing, load_diabetes
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

try:
    data = fetch_california_housing(as_frame=True)
    X = data.data
    y = data.target
    dataset_name = "California Housing"
except Exception:
    fallback = load_diabetes(as_frame=True)
    X = fallback.data
    y = fallback.target
    dataset_name = "Diabetes (fallback)"

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

model = LinearRegression()
model.fit(X_train, y_train)
pred = model.predict(X_test)

print("Dataset:", dataset_name)
print("MAE:", mean_absolute_error(y_test, pred))
print("MSE:", mean_squared_error(y_test, pred))
print("R2:", r2_score(y_test, pred))

plt.figure(figsize=(7, 4))
plt.scatter(y_test, pred, alpha=0.6)
plt.xlabel("Actual")
plt.ylabel("Predicted")
plt.title("Built-in Dataset: Actual vs Predicted")
plt.show()
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Decision_Tree/decision_tree_synthetic.ipynb" -Title "Decision Tree on Synthetic Data" -Objective "Visualize decision boundaries and tree structure using synthetic classification data." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
from sklearn.tree import DecisionTreeClassifier, plot_tree
from sklearn.metrics import accuracy_score

np.random.seed(42)
X = np.random.rand(300, 2)
y = ((X[:, 0] - 0.5) ** 2 + (X[:, 1] - 0.5) ** 2 > 0.08).astype(int)

model = DecisionTreeClassifier(max_depth=4, random_state=42)
model.fit(X, y)
pred = model.predict(X)

xx, yy = np.meshgrid(
    np.linspace(X[:, 0].min(), X[:, 0].max(), 200),
    np.linspace(X[:, 1].min(), X[:, 1].max(), 200),
)
zz = model.predict(np.c_[xx.ravel(), yy.ravel()]).reshape(xx.shape)

plt.figure(figsize=(7, 5))
plt.contourf(xx, yy, zz, alpha=0.3)
plt.scatter(X[:, 0], X[:, 1], c=y, s=20)
plt.title("Decision Boundary (Synthetic)")
plt.show()

plt.figure(figsize=(14, 7))
plot_tree(model, filled=True)
plt.title("Decision Tree Structure")
plt.show()

print("Training accuracy:", accuracy_score(y, pred))
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Decision_Tree/decision_tree_csv_upload.ipynb" -Title "Decision Tree on CSV Upload" -Objective "Train a decision tree classifier from uploaded CSV data and visualize confusion matrix." -MainCode @'
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from google.colab import files
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix

uploaded = files.upload()
file_name = next(iter(uploaded))
df = pd.read_csv(file_name)
display(df.head())

target_col = df.columns[-1]
X = pd.get_dummies(df.drop(columns=[target_col]), drop_first=False)
y = df[target_col]

if y.dtype == "object" or str(y.dtype).startswith("category"):
    y = y.astype("category").cat.codes

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

model = DecisionTreeClassifier(max_depth=6, random_state=42)
model.fit(X_train, y_train)
pred = model.predict(X_test)

print("Accuracy:", accuracy_score(y_test, pred))
print(classification_report(y_test, pred))

cm = confusion_matrix(y_test, pred)
plt.figure(figsize=(6, 4))
sns.heatmap(cm, annot=True, fmt="d", cmap="Blues")
plt.title("Confusion Matrix")
plt.show()
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Decision_Tree/decision_tree_builtin_breast_cancer.ipynb" -Title "Decision Tree on Built-in Breast Cancer Dataset" -Objective "Train and evaluate decision tree using scikit-learn built-in Breast Cancer dataset." -MainCode @'
import matplotlib.pyplot as plt
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier, plot_tree
from sklearn.metrics import accuracy_score, classification_report

data = load_breast_cancer(as_frame=True)
X = data.data
y = data.target

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

model = DecisionTreeClassifier(max_depth=4, random_state=42)
model.fit(X_train, y_train)
pred = model.predict(X_test)

print("Accuracy:", accuracy_score(y_test, pred))
print(classification_report(y_test, pred))

plt.figure(figsize=(18, 8))
plot_tree(
    model,
    feature_names=data.feature_names,
    class_names=data.target_names,
    filled=True,
    fontsize=7,
)
plt.title("Decision Tree - Breast Cancer")
plt.show()
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Random_Forest/random_forest_synthetic_classification.ipynb" -Title "Random Forest Classification on Synthetic Data" -Objective "Train random forest classifier and visualize decision regions." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score

np.random.seed(42)
X = np.random.rand(300, 2)
y = (X[:, 0] + X[:, 1] > 1).astype(int)

model = RandomForestClassifier(n_estimators=120, max_depth=6, random_state=42)
model.fit(X, y)
pred = model.predict(X)

xx, yy = np.meshgrid(
    np.linspace(X[:, 0].min(), X[:, 0].max(), 200),
    np.linspace(X[:, 1].min(), X[:, 1].max(), 200),
)
zz = model.predict(np.c_[xx.ravel(), yy.ravel()]).reshape(xx.shape)

plt.figure(figsize=(7, 5))
plt.contourf(xx, yy, zz, alpha=0.3)
plt.scatter(X[:, 0], X[:, 1], c=y, s=20)
plt.title("Random Forest Classification - Synthetic")
plt.show()

print("Training accuracy:", accuracy_score(y, pred))
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Random_Forest/random_forest_synthetic_regression.ipynb" -Title "Random Forest Regression on Synthetic Data" -Objective "Train random forest regressor and visualize nonlinear fit." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_squared_error, r2_score

np.random.seed(42)
X = np.sort(5 * np.random.rand(200, 1), axis=0)
y = np.sin(X[:, 0]) + 0.15 * np.random.randn(200)

model = RandomForestRegressor(n_estimators=200, random_state=42)
model.fit(X, y)

X_test = np.linspace(0, 5, 300).reshape(-1, 1)
pred = model.predict(X_test)
train_pred = model.predict(X)

plt.figure(figsize=(7, 4))
plt.scatter(X[:, 0], y, s=16, alpha=0.6, label="Actual")
plt.plot(X_test[:, 0], pred, color="red", label="Prediction")
plt.title("Random Forest Regression - Synthetic")
plt.legend()
plt.show()

print("MSE (train):", mean_squared_error(y, train_pred))
print("R2 (train):", r2_score(y, train_pred))
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Random_Forest/random_forest_csv_upload.ipynb" -Title "Random Forest on CSV Upload" -Objective "Train random forest classifier on uploaded CSV dataset and inspect feature importances." -MainCode @'
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from google.colab import files
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

uploaded = files.upload()
file_name = next(iter(uploaded))
df = pd.read_csv(file_name)
display(df.head())

target_col = df.columns[-1]
X = pd.get_dummies(df.drop(columns=[target_col]), drop_first=False)
y = df[target_col]

if y.dtype == "object" or str(y.dtype).startswith("category"):
    y = y.astype("category").cat.codes

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

model = RandomForestClassifier(n_estimators=150, random_state=42)
model.fit(X_train, y_train)
pred = model.predict(X_test)

print("Accuracy:", accuracy_score(y_test, pred))
print(classification_report(y_test, pred))

cm = confusion_matrix(y_test, pred)
plt.figure(figsize=(6, 4))
sns.heatmap(cm, annot=True, fmt="d", cmap="Greens")
plt.title("Confusion Matrix")
plt.show()

importances = pd.Series(model.feature_importances_, index=X.columns).sort_values(ascending=False).head(12)
plt.figure(figsize=(8, 4))
importances.plot(kind="bar")
plt.title("Top Feature Importances")
plt.ylabel("Importance")
plt.show()
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Random_Forest/random_forest_builtin_wine.ipynb" -Title "Random Forest on Built-in Wine Dataset" -Objective "Train multiclass random forest classifier and visualize feature importance." -MainCode @'
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report

data = load_wine(as_frame=True)
X = data.data
y = data.target

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

model = RandomForestClassifier(n_estimators=200, random_state=42)
model.fit(X_train, y_train)
pred = model.predict(X_test)

print("Accuracy:", accuracy_score(y_test, pred))
print(classification_report(y_test, pred))

feat_imp = pd.Series(model.feature_importances_, index=X.columns).sort_values(ascending=False)
plt.figure(figsize=(9, 4))
feat_imp.head(10).plot(kind="bar")
plt.title("Wine Dataset: Top 10 Feature Importances")
plt.ylabel("Importance")
plt.show()
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Naive_Bayes/naive_bayes_synthetic.ipynb" -Title "Naive Bayes on Synthetic Data" -Objective "Train Gaussian Naive Bayes on synthetic data and visualize decision regions." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import accuracy_score

np.random.seed(42)
X = np.random.rand(250, 2)
y = (X[:, 0] + X[:, 1] > 1).astype(int)

model = GaussianNB()
model.fit(X, y)
pred = model.predict(X)

xx, yy = np.meshgrid(
    np.linspace(X[:, 0].min(), X[:, 0].max(), 200),
    np.linspace(X[:, 1].min(), X[:, 1].max(), 200),
)
zz = model.predict(np.c_[xx.ravel(), yy.ravel()]).reshape(xx.shape)

plt.figure(figsize=(7, 5))
plt.contourf(xx, yy, zz, alpha=0.3)
plt.scatter(X[:, 0], X[:, 1], c=y, s=20)
plt.title("Naive Bayes Decision Boundary - Synthetic")
plt.show()

print("Training accuracy:", accuracy_score(y, pred))
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Naive_Bayes/naive_bayes_csv_upload.ipynb" -Title "Naive Bayes on CSV Upload" -Objective "Train Gaussian Naive Bayes classifier on uploaded CSV and evaluate performance." -MainCode @'
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from google.colab import files
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

uploaded = files.upload()
file_name = next(iter(uploaded))
df = pd.read_csv(file_name)
display(df.head())

target_col = df.columns[-1]
X = pd.get_dummies(df.drop(columns=[target_col]), drop_first=False)
y = df[target_col]

if y.dtype == "object" or str(y.dtype).startswith("category"):
    y = y.astype("category").cat.codes

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

model = GaussianNB()
model.fit(X_train, y_train)
pred = model.predict(X_test)

print("Accuracy:", accuracy_score(y_test, pred))
print(classification_report(y_test, pred))

cm = confusion_matrix(y_test, pred)
plt.figure(figsize=(6, 4))
sns.heatmap(cm, annot=True, fmt="d", cmap="Oranges")
plt.title("Confusion Matrix")
plt.show()
'@

Add-Spec -Path "UNIT_2_SUPERVISED/Naive_Bayes/naive_bayes_builtin_digits.ipynb" -Title "Naive Bayes on Built-in Digits Dataset" -Objective "Train Gaussian Naive Bayes for multiclass digit classification." -MainCode @'
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.datasets import load_digits
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

data = load_digits()
X = data.data
y = data.target

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

model = GaussianNB()
model.fit(X_train, y_train)
pred = model.predict(X_test)

print("Accuracy:", accuracy_score(y_test, pred))
print(classification_report(y_test, pred))

cm = confusion_matrix(y_test, pred)
plt.figure(figsize=(8, 6))
sns.heatmap(cm, cmap="Blues")
plt.title("Digits Confusion Matrix")
plt.show()
'@

# Unit III - Unsupervised Learning
Add-Spec -Path "UNIT_3_UNSUPERVISED/KMeans/kmeans_synthetic.ipynb" -Title "K-Means on Synthetic Data" -Objective "Cluster synthetic points and visualize centroids and elbow curve." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

np.random.seed(42)
X = np.random.rand(300, 2)

wcss = []
for k in range(1, 10):
    km = KMeans(n_clusters=k, random_state=42, n_init=10)
    km.fit(X)
    wcss.append(km.inertia_)

plt.figure(figsize=(7, 4))
plt.plot(range(1, 10), wcss, marker="o")
plt.xlabel("Number of clusters (k)")
plt.ylabel("WCSS")
plt.title("Elbow Method")
plt.show()

kmeans = KMeans(n_clusters=3, random_state=42, n_init=10)
labels = kmeans.fit_predict(X)
centroids = kmeans.cluster_centers_

plt.figure(figsize=(7, 5))
plt.scatter(X[:, 0], X[:, 1], c=labels, s=20)
plt.scatter(centroids[:, 0], centroids[:, 1], c="red", marker="X", s=180)
plt.title("K-Means Clusters with Centroids")
plt.show()
'@

Add-Spec -Path "UNIT_3_UNSUPERVISED/KMeans/kmeans_csv_upload.ipynb" -Title "K-Means on CSV Upload" -Objective "Apply K-Means clustering to uploaded CSV dataset after scaling numeric features." -MainCode @'
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from google.colab import files
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans

uploaded = files.upload()
file_name = next(iter(uploaded))
df = pd.read_csv(file_name)
display(df.head())

numeric_df = df.select_dtypes(include=np.number).dropna()
if numeric_df.shape[1] < 2:
    raise ValueError("Need at least two numeric columns for 2D visualization.")

scaler = StandardScaler()
X = scaler.fit_transform(numeric_df)

kmeans = KMeans(n_clusters=3, random_state=42, n_init=10)
labels = kmeans.fit_predict(X)
centroids = kmeans.cluster_centers_

plt.figure(figsize=(7, 5))
plt.scatter(X[:, 0], X[:, 1], c=labels, s=20)
plt.scatter(centroids[:, 0], centroids[:, 1], c="red", marker="X", s=180)
plt.title("K-Means on Uploaded CSV")
plt.xlabel("Feature 1 (scaled)")
plt.ylabel("Feature 2 (scaled)")
plt.show()
'@

Add-Spec -Path "UNIT_3_UNSUPERVISED/KMeans/kmeans_builtin_iris.ipynb" -Title "K-Means on Built-in Iris Dataset" -Objective "Perform K-Means on Iris data and visualize clusters in PCA space." -MainCode @'
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA

iris = load_iris()
X = iris.data

kmeans = KMeans(n_clusters=3, random_state=42, n_init=10)
labels = kmeans.fit_predict(X)

pca = PCA(n_components=2, random_state=42)
X_pca = pca.fit_transform(X)

plt.figure(figsize=(7, 5))
plt.scatter(X_pca[:, 0], X_pca[:, 1], c=labels, s=25)
plt.title("K-Means Clusters on Iris (PCA Projection)")
plt.xlabel("PC1")
plt.ylabel("PC2")
plt.show()
'@

# Unit III - PCA
Add-Spec -Path "UNIT_3_UNSUPERVISED/PCA/pca_synthetic.ipynb" -Title "PCA on Synthetic Data" -Objective "Apply Principal Component Analysis on synthetic data and visualize reduced components." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA

np.random.seed(42)
x1 = np.random.normal(0, 1, 400)
x2 = 0.7 * x1 + np.random.normal(0, 0.5, 400)
x3 = -0.4 * x1 + 0.2 * x2 + np.random.normal(0, 0.4, 400)
X = np.column_stack([x1, x2, x3])

X_scaled = StandardScaler().fit_transform(X)
pca = PCA(n_components=2, random_state=42)
X_pca = pca.fit_transform(X_scaled)

plt.figure(figsize=(7, 5))
plt.scatter(X_pca[:, 0], X_pca[:, 1], alpha=0.7)
plt.title("PCA on Synthetic Data (2 Components)")
plt.xlabel("PC1")
plt.ylabel("PC2")
plt.show()

print("Explained variance ratio:", pca.explained_variance_ratio_)
print("Cumulative explained variance:", np.cumsum(pca.explained_variance_ratio_))
'@

Add-Spec -Path "UNIT_3_UNSUPERVISED/PCA/pca_csv_upload.ipynb" -Title "PCA on CSV Upload" -Objective "Apply PCA on uploaded CSV using numeric columns and visualize principal components." -MainCode @'
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from google.colab import files
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA

uploaded = files.upload()
file_name = next(iter(uploaded))
df = pd.read_csv(file_name)
display(df.head())

numeric_df = df.select_dtypes(include=np.number).dropna()
if numeric_df.shape[1] < 2:
    raise ValueError("Need at least two numeric columns for PCA visualization.")

X_scaled = StandardScaler().fit_transform(numeric_df)
pca = PCA(n_components=2, random_state=42)
X_pca = pca.fit_transform(X_scaled)

plt.figure(figsize=(7, 5))
plt.scatter(X_pca[:, 0], X_pca[:, 1], alpha=0.7)
plt.title("PCA Projection of Uploaded CSV")
plt.xlabel("PC1")
plt.ylabel("PC2")
plt.show()

print("Explained variance ratio:", pca.explained_variance_ratio_)
print("Cumulative explained variance:", np.cumsum(pca.explained_variance_ratio_))
'@

Add-Spec -Path "UNIT_3_UNSUPERVISED/PCA/pca_builtin_iris.ipynb" -Title "PCA on Built-in Iris Dataset" -Objective "Perform PCA on Iris dataset and visualize class separation in principal component space." -MainCode @'
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA

iris = load_iris()
X = iris.data
y = iris.target

X_scaled = StandardScaler().fit_transform(X)
pca = PCA(n_components=2, random_state=42)
X_pca = pca.fit_transform(X_scaled)

plt.figure(figsize=(7, 5))
scatter = plt.scatter(X_pca[:, 0], X_pca[:, 1], c=y, cmap="viridis", s=25)
plt.colorbar(scatter, ticks=[0, 1, 2], label="Class")
plt.title("PCA on Iris Dataset")
plt.xlabel("PC1")
plt.ylabel("PC2")
plt.show()

print("Explained variance ratio:", pca.explained_variance_ratio_)
'@

# Unit III - ICA
Add-Spec -Path "UNIT_3_UNSUPERVISED/ICA/ica_synthetic.ipynb" -Title "ICA on Synthetic Mixed Signals" -Objective "Use Independent Component Analysis to separate mixed synthetic source signals." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import FastICA

np.random.seed(42)
n_samples = 2000
time = np.linspace(0, 8, n_samples)

s1 = np.sin(2 * time)
s2 = np.sign(np.sin(3 * time))
S = np.c_[s1, s2]
S += 0.2 * np.random.normal(size=S.shape)
S /= S.std(axis=0)

A = np.array([[1.0, 1.0], [0.5, 2.0]])
X = S @ A.T

ica = FastICA(n_components=2, random_state=42, whiten="unit-variance")
S_est = ica.fit_transform(X)

fig, axes = plt.subplots(3, 1, figsize=(9, 7), sharex=True)
axes[0].plot(S[:300])
axes[0].set_title("Original Sources")
axes[1].plot(X[:300])
axes[1].set_title("Mixed Signals")
axes[2].plot(S_est[:300])
axes[2].set_title("Recovered Signals (ICA)")
plt.tight_layout()
plt.show()
'@

Add-Spec -Path "UNIT_3_UNSUPERVISED/ICA/ica_csv_upload.ipynb" -Title "ICA on CSV Upload" -Objective "Apply ICA to numeric columns from uploaded CSV and visualize independent components." -MainCode @'
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from google.colab import files
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import FastICA

uploaded = files.upload()
file_name = next(iter(uploaded))
df = pd.read_csv(file_name)
display(df.head())

numeric_df = df.select_dtypes(include=np.number).dropna()
if numeric_df.shape[1] < 2:
    raise ValueError("Need at least two numeric columns for ICA visualization.")

X_scaled = StandardScaler().fit_transform(numeric_df)
n_components = min(3, X_scaled.shape[1])
ica = FastICA(n_components=n_components, random_state=42, whiten="unit-variance", max_iter=1000)
X_ica = ica.fit_transform(X_scaled)

plt.figure(figsize=(7, 5))
plt.scatter(X_ica[:, 0], X_ica[:, 1], alpha=0.7)
plt.title("ICA Projection of Uploaded CSV")
plt.xlabel("IC1")
plt.ylabel("IC2")
plt.show()

print("Output ICA shape:", X_ica.shape)
'@

Add-Spec -Path "UNIT_3_UNSUPERVISED/ICA/ica_builtin_digits.ipynb" -Title "ICA on Built-in Digits Dataset" -Objective "Perform ICA on the Digits dataset and visualize independent component space." -MainCode @'
import matplotlib.pyplot as plt
from sklearn.datasets import load_digits
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import FastICA

digits = load_digits()
X = digits.data
y = digits.target

X_scaled = StandardScaler().fit_transform(X)
ica = FastICA(n_components=2, random_state=42, whiten="unit-variance", max_iter=1000)
X_ica = ica.fit_transform(X_scaled)

plt.figure(figsize=(7, 5))
scatter = plt.scatter(X_ica[:, 0], X_ica[:, 1], c=y, cmap="tab10", s=10)
plt.colorbar(scatter, label="Digit")
plt.title("ICA on Digits Dataset")
plt.xlabel("IC1")
plt.ylabel("IC2")
plt.show()
'@

# Unit IV - Probabilistic and Reinforcement + Gradient Descent
Add-Spec -Path "UNIT_4_PROBABILISTIC_RL/Q_Learning/q_learning_chain_environment.ipynb" -Title "Q-Learning in a Chain Environment" -Objective "Implement Q-learning and visualize reward convergence and learned policy." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt

n_states = 6
terminal_state = n_states - 1
n_actions = 2
q_table = np.zeros((n_states, n_actions))

alpha = 0.2
gamma = 0.95
epsilon = 0.3
epsilon_min = 0.05
epsilon_decay = 0.995
episodes = 500
episode_rewards = []

for _ in range(episodes):
    state = 0
    total_reward = 0.0

    for _step in range(30):
        if np.random.rand() < epsilon:
            action = np.random.randint(n_actions)
        else:
            action = np.argmax(q_table[state])

        next_state = max(0, state - 1) if action == 0 else min(terminal_state, state + 1)
        reward = 1.0 if next_state == terminal_state else -0.02
        done = next_state == terminal_state

        q_table[state, action] += alpha * (
            reward + gamma * np.max(q_table[next_state]) - q_table[state, action]
        )

        total_reward += reward
        state = next_state
        if done:
            break

    epsilon = max(epsilon_min, epsilon * epsilon_decay)
    episode_rewards.append(total_reward)

policy = np.argmax(q_table, axis=1)
policy_symbols = np.array(["L", "R"])[policy]
policy_symbols[terminal_state] = "T"

print("Q-table:\n", q_table)
print("Learned policy by state:", policy_symbols.tolist())

window = 25
moving_avg = np.convolve(episode_rewards, np.ones(window) / window, mode="valid")

plt.figure(figsize=(7, 4))
plt.plot(episode_rewards, alpha=0.4, label="Episode reward")
plt.plot(range(window - 1, episodes), moving_avg, color="red", label="Moving average")
plt.title("Q-Learning Reward Convergence")
plt.xlabel("Episode")
plt.ylabel("Reward")
plt.legend()
plt.show()
'@

Add-Spec -Path "UNIT_4_PROBABILISTIC_RL/Gradient_Descent/gradient_descent_synthetic.ipynb" -Title "Gradient Descent on Synthetic Functions" -Objective "Visualize gradient descent optimization and linear fit convergence." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt

# Part A: Minimize f(x) = x^2
def f(x):
    return x ** 2

def grad(x):
    return 2 * x

x = 5.0
lr = 0.1
history = []
for _ in range(25):
    x = x - lr * grad(x)
    history.append(x)

x_vals = np.linspace(-6, 6, 200)
plt.figure(figsize=(7, 4))
plt.plot(x_vals, f(x_vals))
plt.scatter(history, [f(v) for v in history], color="red", s=20)
plt.title("Gradient Descent on f(x)=x^2")
plt.show()

# Part B: Linear regression with manual GD
np.random.seed(42)
X = 2 * np.random.rand(120)
y = 4 + 3 * X + np.random.randn(120)

w, b = 0.0, 0.0
epochs = 150
lr = 0.1
n = len(X)
costs = []

for _ in range(epochs):
    y_pred = w * X + b
    dw = (-2 / n) * np.sum(X * (y - y_pred))
    db = (-2 / n) * np.sum(y - y_pred)
    w -= lr * dw
    b -= lr * db
    costs.append(np.mean((y - y_pred) ** 2))

plt.figure(figsize=(7, 4))
plt.plot(costs)
plt.title("Cost vs Iterations")
plt.xlabel("Iteration")
plt.ylabel("MSE")
plt.show()

print("Final parameters -> w:", w, "b:", b)
'@

Add-Spec -Path "UNIT_4_PROBABILISTIC_RL/Gradient_Descent/gradient_descent_csv_upload.ipynb" -Title "Gradient Descent Regression on CSV Upload" -Objective "Train a single-feature linear model using manual gradient descent on uploaded CSV." -MainCode @'
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from google.colab import files
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score

uploaded = files.upload()
file_name = next(iter(uploaded))
df = pd.read_csv(file_name)
display(df.head())

numeric_df = df.select_dtypes(include=np.number).dropna()
if numeric_df.shape[1] < 2:
    raise ValueError("Need at least two numeric columns.")

feature_col = numeric_df.columns[0]
target_col = numeric_df.columns[-1]

X = numeric_df[[feature_col]].to_numpy()
y = numeric_df[target_col].to_numpy()

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

mu = X_train.mean(axis=0)
sigma = X_train.std(axis=0) + 1e-8
X_train_n = (X_train - mu) / sigma
X_test_n = (X_test - mu) / sigma

w = np.zeros((1,))
b = 0.0
lr = 0.05
epochs = 300
n = len(X_train_n)
losses = []

for _ in range(epochs):
    pred_train = X_train_n @ w + b
    error = pred_train - y_train
    dw = (2 / n) * (X_train_n.T @ error)
    db = (2 / n) * np.sum(error)
    w -= lr * dw
    b -= lr * db
    losses.append(np.mean(error ** 2))

pred_test = X_test_n @ w + b

print("Feature:", feature_col)
print("Target:", target_col)
print("MSE:", mean_squared_error(y_test, pred_test))
print("R2:", r2_score(y_test, pred_test))

plt.figure(figsize=(7, 4))
plt.plot(losses)
plt.title("Gradient Descent Loss Curve")
plt.xlabel("Iteration")
plt.ylabel("MSE")
plt.show()
'@

Add-Spec -Path "UNIT_4_PROBABILISTIC_RL/Gradient_Descent/gradient_descent_builtin_diabetes.ipynb" -Title "Gradient Descent on Built-in Diabetes Dataset" -Objective "Use manual gradient descent on one Diabetes feature and evaluate convergence." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_diabetes
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score

data = load_diabetes(as_frame=True)
X = data.frame[["bmi"]].to_numpy()
y = data.frame["target"].to_numpy()

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

mu = X_train.mean(axis=0)
sigma = X_train.std(axis=0) + 1e-8
X_train_n = (X_train - mu) / sigma
X_test_n = (X_test - mu) / sigma

w = np.zeros((1,))
b = 0.0
lr = 0.05
epochs = 400
losses = []

for _ in range(epochs):
    pred = X_train_n @ w + b
    err = pred - y_train
    dw = 2 * (X_train_n.T @ err) / len(X_train_n)
    db = 2 * np.mean(err)
    w -= lr * dw
    b -= lr * db
    losses.append(np.mean(err ** 2))

pred_test = X_test_n @ w + b

print("MSE:", mean_squared_error(y_test, pred_test))
print("R2:", r2_score(y_test, pred_test))

plt.figure(figsize=(7, 4))
plt.plot(losses)
plt.title("Training Loss vs Epochs")
plt.xlabel("Epoch")
plt.ylabel("MSE")
plt.show()
'@

Add-Spec -Path "UNIT_4_PROBABILISTIC_RL/reinforcement_and_probabilistic_inference.ipynb" -Title "Reinforcement Learning and Probabilistic Inference" -Objective "Implement basic Q-learning and Bayesian posterior estimation in Colab." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import beta

# Part A: Q-learning in a 1D chain environment
n_states = 6
terminal_state = 5
q_table = np.zeros((n_states, 2))  # actions: 0=left, 1=right
alpha = 0.2
gamma = 0.95
epsilon = 0.2
episodes = 300

for _ in range(episodes):
    state = 0
    done = False
    while not done:
        if np.random.rand() < epsilon:
            action = np.random.randint(0, 2)
        else:
            action = np.argmax(q_table[state])

        next_state = max(0, state - 1) if action == 0 else min(terminal_state, state + 1)
        reward = 1.0 if next_state == terminal_state else -0.01
        done = next_state == terminal_state

        q_table[state, action] = q_table[state, action] + alpha * (
            reward + gamma * np.max(q_table[next_state]) - q_table[state, action]
        )
        state = next_state

print("Learned Q-table:\n", q_table)

# Part B: Bayesian inference for coin bias
np.random.seed(42)
trials = 40
heads_observed = np.random.binomial(1, 0.65, size=trials).sum()
tails_observed = trials - heads_observed

a_prior, b_prior = 1, 1
a_post = a_prior + heads_observed
b_post = b_prior + tails_observed

x = np.linspace(0, 1, 300)
prior = beta.pdf(x, a_prior, b_prior)
posterior = beta.pdf(x, a_post, b_post)

plt.figure(figsize=(7, 4))
plt.plot(x, prior, label="Prior Beta(1,1)")
plt.plot(x, posterior, label=f"Posterior Beta({a_post},{b_post})")
plt.title("Bayesian Inference for Coin Bias")
plt.xlabel("Probability of Heads")
plt.ylabel("Density")
plt.legend()
plt.show()
'@

# Unit V - Model Evaluation
Add-Spec -Path "UNIT_5_MODEL_EVALUATION/model_evaluation_strategies.ipynb" -Title "Model Evaluation and Performance Analysis" -Objective "Evaluate classification and regression models using standard metrics and cross-validation." -MainCode @'
import numpy as np
from sklearn.datasets import load_breast_cancer, load_diabetes
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.linear_model import LogisticRegression, LinearRegression
from sklearn.metrics import (
    accuracy_score,
    precision_score,
    recall_score,
    f1_score,
    mean_absolute_error,
    mean_squared_error,
    r2_score,
)

# Classification metrics
bc = load_breast_cancer(as_frame=True)
Xc = bc.data
yc = bc.target

Xc_train, Xc_test, yc_train, yc_test = train_test_split(
    Xc, yc, test_size=0.2, random_state=42, stratify=yc
)

clf = LogisticRegression(max_iter=4000)
clf.fit(Xc_train, yc_train)
yc_pred = clf.predict(Xc_test)

print("Classification metrics")
print("Accuracy:", accuracy_score(yc_test, yc_pred))
print("Precision:", precision_score(yc_test, yc_pred))
print("Recall:", recall_score(yc_test, yc_pred))
print("F1:", f1_score(yc_test, yc_pred))

cv_scores = cross_val_score(clf, Xc, yc, cv=5, scoring="accuracy")
print("Cross-validation accuracy:", cv_scores)
print("CV mean:", np.mean(cv_scores))

# Regression metrics
diab = load_diabetes(as_frame=True)
Xr = diab.data
yr = diab.target

Xr_train, Xr_test, yr_train, yr_test = train_test_split(
    Xr, yr, test_size=0.2, random_state=42
)

reg = LinearRegression()
reg.fit(Xr_train, yr_train)
yr_pred = reg.predict(Xr_test)

print("\nRegression metrics")
print("MAE:", mean_absolute_error(yr_test, yr_pred))
print("MSE:", mean_squared_error(yr_test, yr_pred))
print("R2:", r2_score(yr_test, yr_pred))
'@

# Unit VI - Deep Learning (RNN, LSTM, CNN)
Add-Spec -Path "UNIT_6_DEEP_LEARNING/RNN/rnn_synthetic_timeseries.ipynb" -Title "RNN on Synthetic Time Series" -Objective "Train a SimpleRNN model for one-step ahead forecasting on synthetic time series." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras import layers, models

np.random.seed(42)
tf.random.set_seed(42)

t = np.linspace(0, 120, 2200)
series = np.sin(0.2 * t) + 0.3 * np.sin(0.05 * t) + 0.1 * np.random.randn(len(t))

window = 30
X, y = [], []
for i in range(len(series) - window):
    X.append(series[i:i + window])
    y.append(series[i + window])

X = np.array(X)[..., np.newaxis]
y = np.array(y)

split = int(0.8 * len(X))
X_train, X_test = X[:split], X[split:]
y_train, y_test = y[:split], y[split:]

model = models.Sequential([
    layers.SimpleRNN(32, input_shape=(window, 1)),
    layers.Dense(1),
])

model.compile(optimizer="adam", loss="mse", metrics=["mae"])
history = model.fit(X_train, y_train, epochs=8, batch_size=32, validation_data=(X_test, y_test), verbose=1)

pred = model.predict(X_test, verbose=0).ravel()

plt.figure(figsize=(8, 4))
plt.plot(y_test[:250], label="Actual")
plt.plot(pred[:250], label="Predicted")
plt.title("RNN Forecast on Synthetic Series")
plt.legend()
plt.show()

print("Final validation MAE:", history.history["val_mae"][-1])
'@ -SetupCode $setupCNN

Add-Spec -Path "UNIT_6_DEEP_LEARNING/RNN/rnn_csv_upload.ipynb" -Title "RNN on CSV Upload Time Series" -Objective "Train SimpleRNN using a single numeric column from uploaded CSV time series data." -MainCode @'
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras import layers, models
from google.colab import files

uploaded = files.upload()
file_name = next(iter(uploaded))
df = pd.read_csv(file_name)
display(df.head())

numeric_df = df.select_dtypes(include=np.number).dropna()
if numeric_df.shape[1] < 1:
    raise ValueError("CSV must contain at least one numeric column for time series.")

series = numeric_df.iloc[:, 0].to_numpy(dtype=np.float32)
series = (series - series.mean()) / (series.std() + 1e-8)

window = 20
X, y = [], []
for i in range(len(series) - window):
    X.append(series[i:i + window])
    y.append(series[i + window])

X = np.array(X)[..., np.newaxis]
y = np.array(y)

if len(X) < 100:
    raise ValueError("Need more rows in CSV to create RNN training sequences.")

split = int(0.8 * len(X))
X_train, X_test = X[:split], X[split:]
y_train, y_test = y[:split], y[split:]

model = models.Sequential([
    layers.SimpleRNN(32, input_shape=(window, 1)),
    layers.Dense(1),
])

model.compile(optimizer="adam", loss="mse", metrics=["mae"])
model.fit(X_train, y_train, epochs=8, batch_size=32, validation_data=(X_test, y_test), verbose=1)

pred = model.predict(X_test, verbose=0).ravel()

plt.figure(figsize=(8, 4))
plt.plot(y_test[:200], label="Actual")
plt.plot(pred[:200], label="Predicted")
plt.title("RNN Forecast on Uploaded CSV Series")
plt.legend()
plt.show()
'@ -SetupCode $setupCNN -Notes "The first numeric column is treated as a univariate time series." 

Add-Spec -Path "UNIT_6_DEEP_LEARNING/RNN/rnn_builtin_imdb.ipynb" -Title "RNN on Built-in IMDB Dataset" -Objective "Train a SimpleRNN model for sentiment classification on IMDB reviews." -MainCode @'
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras import layers, models
from tensorflow.keras.preprocessing import sequence

vocab_size = 10000
max_len = 200

(x_train, y_train), (x_test, y_test) = tf.keras.datasets.imdb.load_data(num_words=vocab_size)
x_train = sequence.pad_sequences(x_train, maxlen=max_len)
x_test = sequence.pad_sequences(x_test, maxlen=max_len)

model = models.Sequential([
    layers.Embedding(vocab_size, 32, input_length=max_len),
    layers.SimpleRNN(32),
    layers.Dense(1, activation="sigmoid"),
])

model.compile(optimizer="adam", loss="binary_crossentropy", metrics=["accuracy"])
history = model.fit(x_train, y_train, epochs=2, batch_size=128, validation_split=0.2, verbose=1)

loss, acc = model.evaluate(x_test, y_test, verbose=0)
print("Test accuracy:", acc)

plt.figure(figsize=(7, 4))
plt.plot(history.history["accuracy"], label="train")
plt.plot(history.history["val_accuracy"], label="val")
plt.title("IMDB SimpleRNN Accuracy")
plt.legend()
plt.show()
'@ -SetupCode $setupCNN

Add-Spec -Path "UNIT_6_DEEP_LEARNING/LSTM/lstm_synthetic_timeseries.ipynb" -Title "LSTM on Synthetic Time Series" -Objective "Train an LSTM model for one-step ahead forecasting on synthetic time series." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras import layers, models

np.random.seed(42)
tf.random.set_seed(42)

t = np.linspace(0, 120, 2200)
series = np.sin(0.2 * t) + 0.3 * np.cos(0.07 * t) + 0.1 * np.random.randn(len(t))

window = 30
X, y = [], []
for i in range(len(series) - window):
    X.append(series[i:i + window])
    y.append(series[i + window])

X = np.array(X)[..., np.newaxis]
y = np.array(y)

split = int(0.8 * len(X))
X_train, X_test = X[:split], X[split:]
y_train, y_test = y[:split], y[split:]

model = models.Sequential([
    layers.LSTM(32, input_shape=(window, 1)),
    layers.Dense(1),
])

model.compile(optimizer="adam", loss="mse", metrics=["mae"])
history = model.fit(X_train, y_train, epochs=8, batch_size=32, validation_data=(X_test, y_test), verbose=1)

pred = model.predict(X_test, verbose=0).ravel()

plt.figure(figsize=(8, 4))
plt.plot(y_test[:250], label="Actual")
plt.plot(pred[:250], label="Predicted")
plt.title("LSTM Forecast on Synthetic Series")
plt.legend()
plt.show()

print("Final validation MAE:", history.history["val_mae"][-1])
'@ -SetupCode $setupCNN

Add-Spec -Path "UNIT_6_DEEP_LEARNING/LSTM/lstm_csv_upload.ipynb" -Title "LSTM on CSV Upload Time Series" -Objective "Train LSTM using a single numeric column from uploaded CSV time series data." -MainCode @'
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras import layers, models
from google.colab import files

uploaded = files.upload()
file_name = next(iter(uploaded))
df = pd.read_csv(file_name)
display(df.head())

numeric_df = df.select_dtypes(include=np.number).dropna()
if numeric_df.shape[1] < 1:
    raise ValueError("CSV must contain at least one numeric column for time series.")

series = numeric_df.iloc[:, 0].to_numpy(dtype=np.float32)
series = (series - series.mean()) / (series.std() + 1e-8)

window = 20
X, y = [], []
for i in range(len(series) - window):
    X.append(series[i:i + window])
    y.append(series[i + window])

X = np.array(X)[..., np.newaxis]
y = np.array(y)

if len(X) < 100:
    raise ValueError("Need more rows in CSV to create LSTM training sequences.")

split = int(0.8 * len(X))
X_train, X_test = X[:split], X[split:]
y_train, y_test = y[:split], y[split:]

model = models.Sequential([
    layers.LSTM(32, input_shape=(window, 1)),
    layers.Dense(1),
])

model.compile(optimizer="adam", loss="mse", metrics=["mae"])
model.fit(X_train, y_train, epochs=8, batch_size=32, validation_data=(X_test, y_test), verbose=1)

pred = model.predict(X_test, verbose=0).ravel()

plt.figure(figsize=(8, 4))
plt.plot(y_test[:200], label="Actual")
plt.plot(pred[:200], label="Predicted")
plt.title("LSTM Forecast on Uploaded CSV Series")
plt.legend()
plt.show()
'@ -SetupCode $setupCNN -Notes "The first numeric column is treated as a univariate time series." 

Add-Spec -Path "UNIT_6_DEEP_LEARNING/LSTM/lstm_builtin_imdb.ipynb" -Title "LSTM on Built-in IMDB Dataset" -Objective "Train an LSTM model for sentiment classification on IMDB reviews." -MainCode @'
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras import layers, models
from tensorflow.keras.preprocessing import sequence

vocab_size = 10000
max_len = 200

(x_train, y_train), (x_test, y_test) = tf.keras.datasets.imdb.load_data(num_words=vocab_size)
x_train = sequence.pad_sequences(x_train, maxlen=max_len)
x_test = sequence.pad_sequences(x_test, maxlen=max_len)

model = models.Sequential([
    layers.Embedding(vocab_size, 32, input_length=max_len),
    layers.LSTM(64),
    layers.Dense(1, activation="sigmoid"),
])

model.compile(optimizer="adam", loss="binary_crossentropy", metrics=["accuracy"])
history = model.fit(x_train, y_train, epochs=2, batch_size=128, validation_split=0.2, verbose=1)

loss, acc = model.evaluate(x_test, y_test, verbose=0)
print("Test accuracy:", acc)

plt.figure(figsize=(7, 4))
plt.plot(history.history["accuracy"], label="train")
plt.plot(history.history["val_accuracy"], label="val")
plt.title("IMDB LSTM Accuracy")
plt.legend()
plt.show()
'@ -SetupCode $setupCNN

Add-Spec -Path "UNIT_6_DEEP_LEARNING/CNN/cnn_synthetic.ipynb" -Title "CNN on Synthetic Image Data" -Objective "Train a simple CNN on generated synthetic line-pattern images." -MainCode @'
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras import layers, models

np.random.seed(42)
tf.random.set_seed(42)

def make_image(label):
    img = np.zeros((28, 28), dtype=np.float32)
    if label == 0:
        c = np.random.randint(6, 22)
        img[:, c - 1:c + 1] = 1.0
    else:
        r = np.random.randint(6, 22)
        img[r - 1:r + 1, :] = 1.0
    img += 0.12 * np.random.randn(28, 28).astype(np.float32)
    return np.clip(img, 0.0, 1.0)

n_samples = 1400
y = np.random.randint(0, 2, size=n_samples)
X = np.array([make_image(lbl) for lbl in y])[..., np.newaxis]

split = 1100
X_train, X_test = X[:split], X[split:]
y_train, y_test = y[:split], y[split:]

model = models.Sequential([
    layers.Conv2D(16, (3, 3), activation="relu", input_shape=(28, 28, 1)),
    layers.MaxPooling2D((2, 2)),
    layers.Conv2D(32, (3, 3), activation="relu"),
    layers.MaxPooling2D((2, 2)),
    layers.Flatten(),
    layers.Dense(64, activation="relu"),
    layers.Dense(2, activation="softmax"),
])

model.compile(optimizer="adam", loss="sparse_categorical_crossentropy", metrics=["accuracy"])
history = model.fit(X_train, y_train, validation_data=(X_test, y_test), epochs=5, batch_size=32, verbose=1)

loss, acc = model.evaluate(X_test, y_test, verbose=0)
print("Test accuracy:", acc)

plt.figure(figsize=(8, 3))
for i in range(6):
    plt.subplot(2, 3, i + 1)
    plt.imshow(X_test[i, :, :, 0], cmap="gray")
    plt.title(f"Label: {y_test[i]}")
    plt.axis("off")
plt.tight_layout()
plt.show()

plt.figure(figsize=(7, 4))
plt.plot(history.history["accuracy"], label="train")
plt.plot(history.history["val_accuracy"], label="val")
plt.title("CNN Accuracy Curves")
plt.legend()
plt.show()
'@ -SetupCode $setupCNN

Add-Spec -Path "UNIT_6_DEEP_LEARNING/CNN/cnn_csv_upload.ipynb" -Title "CNN on CSV Upload Data" -Objective "Train CNN from uploaded flattened-image CSV (label in first column, pixels in remaining columns)." -MainCode @'
import numpy as np
import pandas as pd
import tensorflow as tf
from tensorflow.keras import layers, models
from google.colab import files
from sklearn.model_selection import train_test_split

uploaded = files.upload()
file_name = next(iter(uploaded))
df = pd.read_csv(file_name)
display(df.head())

label_col = df.columns[0]
y = df[label_col].astype(int).to_numpy()
X = df.drop(columns=[label_col]).to_numpy(dtype=np.float32)

side = int(np.sqrt(X.shape[1]))
if side * side != X.shape[1]:
    raise ValueError("Pixel count must form a square image (e.g., 784 for 28x28).")

X = (X / 255.0).reshape(-1, side, side, 1)
num_classes = len(np.unique(y))

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

model = models.Sequential([
    layers.Conv2D(16, (3, 3), activation="relu", input_shape=(side, side, 1)),
    layers.MaxPooling2D((2, 2)),
    layers.Conv2D(32, (3, 3), activation="relu"),
    layers.MaxPooling2D((2, 2)),
    layers.Flatten(),
    layers.Dense(64, activation="relu"),
    layers.Dense(num_classes, activation="softmax"),
])

model.compile(optimizer="adam", loss="sparse_categorical_crossentropy", metrics=["accuracy"])
model.fit(X_train, y_train, epochs=5, batch_size=32, validation_data=(X_test, y_test), verbose=1)

loss, acc = model.evaluate(X_test, y_test, verbose=0)
print("Test accuracy:", acc)
'@ -SetupCode $setupCNN -Notes "Expected CSV format: first column = class label, remaining columns = flattened grayscale pixels."

Add-Spec -Path "UNIT_6_DEEP_LEARNING/CNN/cnn_builtin_fashion_mnist.ipynb" -Title "CNN on Built-in Fashion-MNIST Dataset" -Objective "Train and evaluate a CNN using TensorFlow built-in Fashion-MNIST dataset." -MainCode @'
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras import layers, models

(X_train, y_train), (X_test, y_test) = tf.keras.datasets.fashion_mnist.load_data()

X_train = (X_train / 255.0).reshape(-1, 28, 28, 1)
X_test = (X_test / 255.0).reshape(-1, 28, 28, 1)

model = models.Sequential([
    layers.Conv2D(32, (3, 3), activation="relu", input_shape=(28, 28, 1)),
    layers.MaxPooling2D((2, 2)),
    layers.Conv2D(64, (3, 3), activation="relu"),
    layers.MaxPooling2D((2, 2)),
    layers.Flatten(),
    layers.Dense(128, activation="relu"),
    layers.Dense(10, activation="softmax"),
])

model.compile(optimizer="adam", loss="sparse_categorical_crossentropy", metrics=["accuracy"])
history = model.fit(X_train, y_train, epochs=5, batch_size=64, validation_split=0.1, verbose=1)

loss, acc = model.evaluate(X_test, y_test, verbose=0)
print("Test accuracy:", acc)

plt.figure(figsize=(7, 4))
plt.plot(history.history["accuracy"], label="train")
plt.plot(history.history["val_accuracy"], label="val")
plt.title("Fashion-MNIST CNN Accuracy")
plt.legend()
plt.show()
'@ -SetupCode $setupCNN

# Write all notebooks
foreach ($nb in $notebooks) {
    Write-Notebook -Spec $nb
}

$readme = @'
# CS23603 Machine Learning - Google Colab Lab Pack

This folder contains complete, Colab-ready lab notebooks for CS23603, organized by units.

## Structure
- UNIT_1_INTRODUCTION
  - Tool workflow, benchmark repositories, Python library basics
- UNIT_2_SUPERVISED
  - Linear Regression, Multiple Regression, Decision Tree, Random Forest, Naive Bayes
  - Each algorithm includes synthetic, CSV upload, and built-in dataset notebooks
- UNIT_3_UNSUPERVISED
    - K-Means notebooks for synthetic, CSV upload, and built-in Iris dataset
    - PCA notebooks for synthetic, CSV upload, and built-in Iris dataset
    - ICA notebooks for synthetic, CSV upload, and built-in Digits dataset
- UNIT_4_PROBABILISTIC_RL
    - Q-Learning notebook
  - Gradient Descent notebooks (synthetic, CSV, built-in)
  - Reinforcement learning and probabilistic inference notebook
- UNIT_5_MODEL_EVALUATION
  - Performance metrics and cross-validation notebook
- UNIT_6_DEEP_LEARNING
    - RNN notebooks for synthetic, CSV upload, and built-in IMDB dataset
    - LSTM notebooks for synthetic, CSV upload, and built-in IMDB dataset
  - CNN notebooks for synthetic, CSV upload, and built-in Fashion-MNIST

## Colab usage
1. Open a notebook in Google Colab.
2. Run the setup cell first.
3. For CSV notebooks, upload your dataset when prompted.
4. Run the main code cell and capture outputs/screenshots for lab record.
'@

Set-Content -Path (Join-Path $root "README.md") -Value $readme -Encoding utf8

Write-Host "Created CS23603 lab pack at: $root"
Write-Host "Total notebooks created: $($notebooks.Count)"
