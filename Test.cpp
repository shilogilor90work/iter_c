#include "doctest.h"
#include <iostream>
#include <vector>

#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"


using namespace itertools;
using namespace std;

struct lessThan3 {
    bool operator()(int i) const { return i < 3; }
};
struct moreThan10 {
    bool operator()(int i) const { return i > 10; }
};

 TEST_CASE("Check Initialize") {
   vector<int> vecInt = {1,2,3,4};
   vector<string> vecString = {"Hello", "Bye", "Adam"};
   CHECK_NOTHROW(range(5));
   CHECK_NOTHROW(range(5,9));
   CHECK_NOTHROW(range(5,9,2));
   CHECK_NOTHROW(accumulate(vecString));
   CHECK_NOTHROW(accumulate(range(5,9), [](int x, int y){return x*y;}));
   CHECK_NOTHROW(filterfalse(lessThan3{}, vecInt));
   CHECK_NOTHROW(filterfalse([](int i){return i%2==0;}, range(5,9)));
   CHECK_NOTHROW(compress(string("abcd"), vector<bool>({true,true,false,true})));
   CHECK_NOTHROW(compress(range(5,9), vector<bool>({true,true,false,true})));
 }
 TEST_CASE("Check range single value") {
   CHECK(range(5)[0]==0);
   CHECK(range(5)[1]==1);
   CHECK(range(5)[2]==2);
   CHECK(range(5)[3]==3);
   CHECK(range(5)[4]==4);
   CHECK(range(5).size()==5);

   CHECK(range(3)[0]==0);
   CHECK(range(3)[1]==1);
   CHECK(range(3)[2]==2);
   CHECK(range(3).size()==3);
 }

 TEST_CASE("Check range two values") {
   CHECK(range(2,7)[0]==2);
   CHECK(range(2,7)[1]==3);
   CHECK(range(2,7)[2]==4);
   CHECK(range(2,7)[3]==5);
   CHECK(range(2,7)[4]==6);
   CHECK(range(2,7).size()==5);

   CHECK(range(20,25)[0]==20);
   CHECK(range(20,25)[1]==21);
   CHECK(range(20,25)[2]==22);
   CHECK(range(20,25)[3]==23);
   CHECK(range(20,25)[4]==24);
   CHECK(range(20,25).size()==5);
 }

 TEST_CASE("Check range three values") {
   CHECK(range(2,20,3)[0]==2);
   CHECK(range(2,20,3)[1]==5);
   CHECK(range(2,20,3)[2]==8);
   CHECK(range(2,20,3)[3]==11);
   CHECK(range(2,20,3)[4]==14);
   CHECK(range(2,20,3)[5]==17);
   CHECK(range(2,20,3).size()==6);

   CHECK(range(20,2,-3)[0]==20);
   CHECK(range(20,2,-3)[1]==17);
   CHECK(range(20,2,-3)[2]==14);
   CHECK(range(20,2,-3)[3]==11);
   CHECK(range(20,2,-3)[4]==8);
   CHECK(range(20,2,-3)[5]==5);
   CHECK(range(20,2,-3).size()==6);
 }

 TEST_CASE("Check accumulate") {
   vector<string> vecString = {"Hello", "Bye", "Adam"};
   CHECK(accumulate(vecString)[0]=="Hello");
   CHECK(accumulate(vecString)[1]=="HelloBye");
   CHECK(accumulate(vecString)[2]=="HelloByeAdam");
   CHECK(accumulate(vecString).size()==3);
 }

 TEST_CASE("Check accumulate with function") {
   CHECK(accumulate(range(5,9), [](int x, int y){return x*y;})[0]==5);
   CHECK(accumulate(range(5,9), [](int x, int y){return x*y;})[1]==30);
   CHECK(accumulate(range(5,9), [](int x, int y){return x*y;})[2]==210);
   CHECK(accumulate(range(5,9), [](int x, int y){return x*y;})[3]==1680);
   CHECK(accumulate(range(5,9), [](int x, int y){return x*y;}).size()==4);

 }

 TEST_CASE("Check accumulate with function") {
   CHECK(accumulate(range(1,6), [](int x, int y){return x+y*y;})[0]==1);
   CHECK(accumulate(range(1,6), [](int x, int y){return x+y*y;})[1]==5);
   CHECK(accumulate(range(1,6), [](int x, int y){return x+y*y;})[2]==14);
   CHECK(accumulate(range(1,6), [](int x, int y){return x+y*y;})[3]==30);
   CHECK(accumulate(range(1,6), [](int x, int y){return x+y*y;})[4]==55);
   CHECK(accumulate(range(1,6), [](int x, int y){return x+y*y;}).size()==5);
 }
 TEST_CASE("Check filterfalse") {
   vector<int> vecInt = {1,2,3,4};
   CHECK(filterfalse(lessThan3{}, vecInt)[0]==3);
   CHECK(filterfalse(lessThan3{}, vecInt)[1]==4);
   CHECK(filterfalse(lessThan3{}, vecInt).size()==2);

   vecInt = {1,2,3,4,20,40,7,10};
   CHECK(filterfalse(moreThan10{}, vecInt)[0]==1);
   CHECK(filterfalse(moreThan10{}, vecInt)[1]==2);
   CHECK(filterfalse(moreThan10{}, vecInt)[2]==3);
   CHECK(filterfalse(moreThan10{}, vecInt)[3]==4);
   CHECK(filterfalse(moreThan10{}, vecInt)[4]==7);
   CHECK(filterfalse(moreThan10{}, vecInt)[5]==10);
   CHECK(filterfalse(moreThan10{}, vecInt).size()==6);
 }
 TEST_CASE("Check filterfalse with function") {
   CHECK(filterfalse([](int i){return i%2==0;}, range(5,9))[0]==5);
   CHECK(filterfalse([](int i){return i%2==0;}, range(5,9))[1]==7);
   CHECK(filterfalse([](int i){return i%2==0;}, range(5,9)).size()==2);

 }
 TEST_CASE("Check filterfalse with function sqrt") {
   CHECK(filterfalse([](int i){return sqrt(i) - floor(sqrt(i)) != 0;}, range(30))[0]==0);
   CHECK(filterfalse([](int i){return sqrt(i) - floor(sqrt(i)) != 0;}, range(30))[1]==1);
   CHECK(filterfalse([](int i){return sqrt(i) - floor(sqrt(i)) != 0;}, range(30))[2]==4);
   CHECK(filterfalse([](int i){return sqrt(i) - floor(sqrt(i)) != 0;}, range(30))[3]==9);
   CHECK(filterfalse([](int i){return sqrt(i) - floor(sqrt(i)) != 0;}, range(30))[4]==16);
   CHECK(filterfalse([](int i){return sqrt(i) - floor(sqrt(i)) != 0;}, range(30))[5]==25);
   CHECK(filterfalse([](int i){return sqrt(i) - floor(sqrt(i)) != 0;}, range(30)).size()==6);
 }


 TEST_CASE("Check compress") {
   CHECK(compress(string("abcd"), vector<bool>({true,true,false,true}))[0]=='a');
   CHECK(compress(string("abcd"), vector<bool>({true,true,false,true}))[1]=='b');
   CHECK(compress(string("abcd"), vector<bool>({true,true,false,true}))[2]=='d');
   CHECK(compress(string("abcd"), vector<bool>({true,true,false,true})).size()==3);

   CHECK(compress(string("aaaa"), vector<bool>({true,true,false,true}))[0]=='a');
   CHECK(compress(string("aaaa"), vector<bool>({true,true,false,true}))[1]=='a');
   CHECK(compress(string("aaaa"), vector<bool>({true,true,false,true}))[2]=='a');
   CHECK(compress(string("aaaa"), vector<bool>({true,true,false,true})).size()==3);

   CHECK(compress(string("abcd"), vector<bool>({false,true,true,true}))[0]=='b');
   CHECK(compress(string("abcd"), vector<bool>({false,true,true,true}))[1]=='c');
   CHECK(compress(string("abcd"), vector<bool>({false,true,true,true}))[2]=='d');
   CHECK(compress(string("abcd"), vector<bool>({false,true,true,true})).size()==3);

   CHECK(compress(range(5,9), vector<bool>({true,true,false,true}))[0]==5);
   CHECK(compress(range(5,9), vector<bool>({true,true,false,true}))[1]==6);
   CHECK(compress(range(5,9), vector<bool>({true,true,false,true}))[2]==8);
   CHECK(compress(range(5,9), vector<bool>({true,true,false,true})).size()==3);

   CHECK(compress(range(1,5), vector<bool>({true,true,false,true}))[0]==1);
   CHECK(compress(range(1,5), vector<bool>({true,true,false,true}))[1]==2);
   CHECK(compress(range(1,5), vector<bool>({true,true,false,true}))[2]==4);
   CHECK(compress(range(1,5), vector<bool>({true,true,false,true})).size()==3);

   CHECK(compress(range(5,9), vector<bool>({false,true,true,true}))[0]==6);
   CHECK(compress(range(5,9), vector<bool>({false,true,true,true}))[1]==7);
   CHECK(compress(range(5,9), vector<bool>({false,true,true,true}))[2]==8);
   CHECK(compress(range(5,9), vector<bool>({false,true,true,true})).size()==3);
 }
