
from copy import deepcopy
import numpy
import pandas
from matplotlib import pyplot



pyplot.rcParams['figure.figsize'] = (16, 9)
pyplot.style.use('ggplot')

data = pandas.read_csv('xclara.csv')
print(data.shape)
data.head()


f1 = data['V1'].values
f2 = data['V2'].values
X = numpy.array(list(zip(f1, f2)))
pyplot.scatter(f1, f2, c='black', s=7)