#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class UserLogin {
  private:
    unordered_map<string, string> table;

  public:
    UserLogin();  // default constructor

    void readIn(const string& filename);  // add data from file to hash table
    size_t numberOfUsers();  // return the number of users
    string passWordCheck(const string& userName);  // returns the passWord of the given user
    size_t wordBucketIdMethod1(const string& userName);  // return the bucket number where the given user is located
    size_t wordBucketIdMethod2(const string& userName);  // another way to find the bucket number where the given user is located
    bool validateUser(const string& userName);  // look up given user
    bool authenticateUser(const string& userName, const string& passWord);  // authenticate given user and password
};

UserLogin::UserLogin() {
}

void UserLogin::readIn(const string& filename) {
  std::ifstream inFile(filename);
  std::string username;
  std::string password;

  while (inFile >> username >> password) {
    table.insert(std::make_pair(username, password));
  }
}

size_t UserLogin::numberOfUsers() {
  return table.size();
}

string UserLogin::passWordCheck(const string& userName) {
  auto it = table.find(userName);

  while (it != table.end()) {
    return it->second;
  }
  return "Non-existent User";
}

size_t UserLogin::wordBucketIdMethod1(const string& userName) {
  return table.hash_function()(userName) % table.bucket_count();
}

size_t UserLogin::wordBucketIdMethod2(const string& userName) {
  return table.bucket(userName);
}

bool UserLogin::validateUser(const string& userName) {
  auto it = table.find(userName);

  if (it != table.end()) {
    return true;
  }
  return false;
}

bool UserLogin::authenticateUser(const string& userName, const string& passWord) {
  auto authUser = table.find(userName);

  if (authUser == table.end()) {
    return false;
  }
  return authUser->second == passWord;
}
