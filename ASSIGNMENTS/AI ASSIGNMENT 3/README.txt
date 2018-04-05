
Data set (Training and test sets are given separately) is the OCR hand written data available at   https://sites.google.com/site/viswanathpulabaigari/data-sets    It is 192 dimensional, 10 class problem. {see the web-site for details}

Task_1:  Find k to be used in k-nearest neighbor classifier (k-NNC) using a 3-fold cross validation. Give the results in your report. You can draw a plot.
              With k value thus found employ k-NNC and find the error rate. Report this in your report.

Task_2:  You should read about "the Naive Bayes classification".  Employ the Naive Bayes classifier with the above mentioned data set. You can use log of the posterior (to overcome the small numbers problem). Report about your observations in your report.



The given data is a discrete one. Each feature can take one of values 0,1,2,3,4.  The probability of occurrence of a particular feature value is its frequency ratio. Let us name features as f1, f2, ...,f192. For example, P(f3 = 2 | class 1) can be found as --
1. Let the class 1 training examples size be n1.
2. In class 1 training set, let the number of times f3 = 2  be m.
3. Then  P(f3 = 2 | class 1) = m/n1.  That is, the frequency ratio using how many times f3 is 2  in class 1 training set, divided by the total number of class 1 training examples.

You should use the Navie Bayes assumption that the features are independent while finding the class conditional probabilities. That is, for example, P(f1=1,f2=4,...,f192=0|class 1) = P(f1=1 | class 1) P(f2=4 | class 1) ...P(f192=0 | class 1).

Because multiplication of small numbers becomes very small (often, the machine might say that the result is zero), I advised usage of the logarithm. So 
log P(f1=1,f2=4,...,f192=0|class 1) = log P(f1=1 | class 1) + log P(f2=4 | class 1) +...+ log P(f192=0 | class 1).
Note base of the logarithm could be e (or even base 10 should not do any harm to the final result because we are looking for some maximum quantity).
