/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Yu Jing <yu@argcv.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **/
#ifndef ARGCV_IR_INDEX_ANALYZER_ANALYZER_HH
#define ARGCV_IR_INDEX_ANALYZER_ANALYZER_HH

#include <string>
#include <vector>

#include "token_seeker.hh"
#include "tokenlizer.hh"

namespace argcv {
namespace ir {
namespace index {
namespace analyzer {
class analyzer : public token_seeker {
 public:
  explicit analyzer(tokenlizer* _t) : token_seeker(), _t(_t) {}

  std::vector<std::string> to_vec() {
    std::vector<std::string> _v;
    std::string s;
    reset();
    while (next(&s)) _v.push_back(s);
    return _v;
  }

 protected:
  tokenlizer* _t;
};
}  // namespace analyzer
}  // namespace index
}  // namespace ir
}  // namespace argcv

#endif  //  ARGCV_IR_INDEX_ANALYZER_ANALYZER_HH
