/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
  if(s.empty()){return T();}
  if(s.size() == 1){return s.top();}
  T top = s.top();
  s.pop();
  T result = top + sum(s);
  s.push(top);
  return result;


    // Your code here
    // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of
 * square bracket characters, [, ], and other characters. This function will return
 * true if and only if the square bracket characters in the given
 * string are balanced. For this to be true,
 * all brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is balanced,
 * "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is balanced.
 *
 * For this function, you may only create a single local variable of type stack<char>!
 * No other stack or queue local objects may be declared. Note that you may still
 * declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
  stack<char> s;
  int leftcount = 0;
  int rightcount = 0;
  int size = input.size();
  for(int x = 0; x < size; x++){
    if(input.front() == '['){
      leftcount++;
    }
    if(input.front() == ']'){
      rightcount++;
    }
    if(leftcount < rightcount){
      return false;
    }
    input.push(input.front());
    input.pop();
  }
    return leftcount == rightcount;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> qq;
    int size = q.size();
    int start = 0;
    for(int count = 1; start < size; count++){
      if(count % 2 == 1){
        for(int i = 0; i < count && start < size; i++){
          q.push(q.front());
          q.pop();
          start++;
        }
      } else{
        int a = 0;
        for(int i = 0; i < count && start < size; i++){
          s.push(q.front());
          q.pop();
          start++;
          a++;
        }
        for(int i = 0; i < a; i++){
          q.push(s.top());
          s.pop();
        }
      }
    }
    // optional: queue<T> q2;

    // Your code here
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note The back of the queue corresponds to the top of the stack!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional
    T temp1;
    T temp2;
    if(s.size()==0)
      return true;
    temp1 = s.top();
    s.pop();
    retval = verifySame(s, q);
    temp2 = q.front();
    q.pop();
    retval = (retval&&(temp1 == temp2));
    q.push(temp2);
    s.push(temp1);
    // Your code here

    return retval;
}

}
