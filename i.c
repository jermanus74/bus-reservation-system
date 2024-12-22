#include <stdio.h>
int main()
{
printf("Create a system to check if student grade is A,B,C,D OR F BASED ON SCORE\n");
float score;
    printf("%f\n",score);
    printf("Enter score to check grade: ");
    scanf("%f",&score);
    printf("%.2f\n",score);

    if(score <= 90){
        printf("you got an 'A+', YOU ARE A GENIUS...\n");

    }
  else if(score>=75){
      printf("you got an 'A'\n");
  }else if(score>65){
      printf("you got a 'B'\n");
  }else if(score>45){
      printf("you got a 'C'\n");
  }else if(score>30){
      printf("you got a 'D'\n");
  }else{
      printf("you got a 'F'\n");
  }
    return 0;
}