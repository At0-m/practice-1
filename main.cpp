#include <iostream>
#include <fstream>


bool StrEql(const char* s1, const char* s2)
{
  while(*s1 == *s2 && *s1 != '\0')
  {
    s1++;
    s2++;
  }
  if(*s1 == '\0' && *s2 == '\0'){
    return true;
  }
  return false;
}


bool IsAlpha(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}


int main(int argc, char** argv) {
  char* word = nullptr;
  char* file_name = nullptr;
  for(int i = 1; i < argc; i++)
  {
    if(StrEql(argv[i-1], "--word")){
      word = argv[i];
    }
    else if(StrEql(argv[i-1], "--file")){
      file_name = argv[i];
    }
  }

  if(word == nullptr || file_name == nullptr)
  {
    std::cout << "Arguments list error" << std::endl;
    return 1;
  }

  bool mask[255];
  int letters_count = 0;
  int count_diff_let = 0;

  for(int i = 0; i < 255; i++)
  {
    mask[i] = false;
  }

  for(int i = 0; word[i] != '\0'; i++)
  {
    char c = word[i];
    if(!IsAlpha(c))
    {
      std::cout << "Word must consist only of Latin letters" << std::endl;
      return 1;
    }
    mask[c] = true;
    letters_count++;
    if(letters_count > 32)
    {
      std::cout << "Word is too long" << std::endl;
      return 1;
    }
  }

  for(int i = 0; i < 255; i++)
  {
    count_diff_let += mask[i];
  }

  std::ifstream input(file_name);
  if(!input)
  {
    std::cout << "Can't open file" << std::endl;
    return 1;
  }

  char buffer[256];
  int count = 0;
  
  while(input >> buffer)
  {
    int count_common_let = 0;
    for(int i = 0; buffer[i] != '\0'; i++){
      count_common_let += mask[buffer[i]];
    }
    if(count_common_let >= count_diff_let){
      count++;
    }
  }
  
  std::cout << count << std::endl;
  
  return 0;
}
