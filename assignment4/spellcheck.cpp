#include "spellcheck.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  /* TODO: Implement this method */
  Corpus tokens;
  
  auto cuts = find_all(source.begin(),  source.end(), [&source](char ch) {
    return std::isspace(static_cast<unsigned char>(ch));
  });

  std::transform(cuts.begin(), std::prev(cuts.end()), std::next(cuts.begin()), 
    std::inserter(tokens, tokens.end()), [&source](auto begin, auto end) {
      return Token(source, begin, end);
  });

  std::erase_if(tokens, [](const Token &t) {
    return t.content.empty();
  });

  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  namespace rv = std::ranges::views;
  auto view = source 
    | rv::filter([&dictionary](const Token &t) {
        return !dictionary.contains(t.content);
      })
    | rv::transform([&dictionary](const Token &t) {
        auto valid = dictionary | rv::filter([&t](const std::string &word) {
          return levenshtein(t.content, word) == 1;
        });

        std::set<std::string> res(valid.begin(), valid.end());
        return Misspelling {t, std::move(res)};
      })
    | rv::filter([](const Misspelling &m) {
      return !m.suggestions.empty();
    });

    std::set<Misspelling> ans(view.begin(), view.end());
    return ans;
};

/* Helper methods */

#include "utils.cpp"