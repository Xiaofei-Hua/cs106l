/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <exception>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Xiaofei Hua"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  // STUDENT TODO: Implement this function.
  std::set<std::string> res;
  std::ifstream ifs(filename);

  if (ifs.is_open()) {
    std::string str;
    while (std::getline(ifs, str)) {
      if (str.empty()) {
        continue;
      }
      res.insert(str);
    }
    ifs.close();
  }

  return res;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  // STUDENT TODO: Implement this function.

  std::queue<const std::string*> res;
  auto p = name.find(' ');
  if (p == std::string::npos || p + 1 >= name.length()) {
    return res;
  }
  //assert(p != std::string::npos);
  auto fst = name[0];
  auto lst = name[p + 1];
  
  for (const auto &str : students) {
    auto q = str.find(' ');
    if (q == std::string::npos || q + 1 >= str.length()) {
      continue;
    }
    auto f = str[0];
    auto g = str[q + 1];
    if (f == fst && g == lst) {
      res.push(&str);
    }
  }
  return res;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  std::string ans;
  if (matches.empty()) {
    ans = "NO MATCHES FOUND.";
  } else {
    ans = *(matches.front());
  }
  return ans;
  // STUDENT TODO: Implement this function.
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
