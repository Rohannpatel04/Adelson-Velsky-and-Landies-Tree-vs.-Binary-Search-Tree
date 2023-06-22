#include<cstdio>
#include<iostream>
#include<ctime>
#include <string>
#include <random>
#include<functional>

#include "BinarySearchTree.h"
#include "AVLTree.h"

using namespace std;

void run_dist(vector<pair<double, double>> to_insert, vector<double> to_find, vector<double> to_remove) {
  BinarySearchTree<double> bst;
  AVLTree<double> avl;
  
   clock_t start = clock();

  for (auto number : to_insert) {
    bst.Insert(number.first, number.second);
  }
  for (auto number : to_find) {
    bst.Find(number);
  }
  for (auto number : to_remove) {
    bst.Remove(number);
  }
  
   clock_t stop = clock();
  cout << "BST: " << (stop - start)/double(CLOCKS_PER_SEC) << endl;
  
   start = clock();

  for (auto number : to_insert) {
    avl.Insert(number.first, number.second);
  }
  for (auto number : to_find) {
    avl.Find(number);
  }
  for (auto number : to_remove) {
    avl.Remove(number);
  }
  
   stop = clock();
  cout << "AVL: " << (stop - start)/double(CLOCKS_PER_SEC) << endl << endl << endl;
  
}

int main()
{
  const unsigned short data_size = 10000;  // number of experiments
  const double param1 = 1000000.0, param2 = 50000.0;
  default_random_engine generator;
  normal_distribution<double> normal(param1, param2);
  lognormal_distribution<double> lognormal(param1, param2);
  chi_squared_distribution<double> chi(param1);
  cauchy_distribution<double> cauchy(param1, param2);
  uniform_real_distribution<double> uniform(0.0, 5000000.0);
  
  uniform_real_distribution<double> uni(0.0, (double)data_size);
  student_t_distribution<double> student(param1);
  
  cout << "Normal" << endl;
  vector<pair<double, double>> test;
  vector<double> t_find;
  vector<double> t_remove;
  for (int i=0; i<data_size; ++i) {
    double number = normal(generator);
    t_find.push_back(normal(generator));
    t_remove.push_back(normal(generator));
    test.push_back(make_pair(number,number));
  }
  run_dist(test, t_find, t_remove);
  test.clear();
  t_find.clear();
  t_remove.clear();
  
  // lognormal
  cout << "LogNormal" << endl;
  for (int i=0; i<data_size; ++i) {
    double number = lognormal(generator);
    t_find.push_back(lognormal(generator));
    t_remove.push_back(lognormal(generator));
    test.push_back(make_pair(number,number));
  }
  run_dist(test, t_find, t_remove);
  test.clear();
  t_find.clear();
  t_remove.clear();
  
  // chi squared
  cout << "Chi Squared" << endl;
  for (int i=0; i<data_size; ++i) {
    double number = cauchy(generator);
    t_find.push_back(cauchy(generator));
    t_remove.push_back(cauchy(generator));
    test.push_back(make_pair(number,number));
  }
  run_dist(test, t_find, t_remove);
  test.clear();
  t_find.clear();
  t_remove.clear();
  // cauchy
  cout << "Cauchy" << endl;
  for (int i=0; i<data_size; ++i) {
    double number = cauchy(generator);
    t_find.push_back(cauchy(generator));
    t_remove.push_back(cauchy(generator));
    test.push_back(make_pair(number,number));
  }
  run_dist(test, t_find, t_remove);
  test.clear();
  t_find.clear();
  t_remove.clear();
// uniform
  cout << "Uniform" << endl;
  for (int i=0; i<data_size; ++i) {
    double number = uniform(generator);
    t_find.push_back(uniform(generator));
    t_remove.push_back(uniform(generator));
    test.push_back(make_pair(number,number));
  }
  run_dist(test, t_find, t_remove);
  test.clear();
  t_find.clear();
  t_remove.clear();
  
  // student
  cout << "Student" << endl;
  for (int i=0; i<data_size; ++i) {
    double number = student(generator);
    t_find.push_back(student(generator));
    t_remove.push_back(student(generator));
    test.push_back(make_pair(number,number));
  }
  run_dist(test, t_find, t_remove);
  test.clear();
  t_find.clear();
  t_remove.clear();
  
  //in order
  cout << "In Order" << endl;
  for (int i=0; i<data_size; ++i) {
    double f_hash = (double)uni(generator);
    double r_hash = (double)uni(generator);
    
    t_find.push_back(f_hash);
    t_remove.push_back(r_hash);
    test.push_back(make_pair(double(i),(double)i));
  }
  run_dist(test, t_find, t_remove);
  test.clear();
  t_find.clear();
  t_remove.clear();
  // hashed
    cout << "Hashed" << endl;
  
  for (int i=0; i<data_size; ++i) {
    double d_hash = hash<double>{}((double)i);
    double f_hash = hash<double>{}((double)uni(generator));
    double r_hash = hash<double>{}((double)uni(generator));
    
    t_find.push_back(f_hash);
    t_remove.push_back(r_hash);
    test.push_back(make_pair(d_hash,(double)i));
  }
  run_dist(test, t_find, t_remove);
  test.clear();
  t_find.clear();
  t_remove.clear();
  
  return 0;
}
