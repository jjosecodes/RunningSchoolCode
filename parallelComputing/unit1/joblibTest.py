import warnings

warnings.filterwarnings("ignore")

import joblib
import sklearn
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPRegressor

import shapiq

print(f"shapiq version: {shapiq.__version__}")
{"scikit-learn": sklearn.__version__, "joblib": joblib.__version__}