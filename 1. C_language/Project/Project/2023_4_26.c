//#define _CRT_SECURE_NO_WARNINGS_ // 경고 메세지 제거
#include <stdio.h>// 함수 정의가 들어가 있다.
#include <stdlib.h>

void main() // 하나만 존재 (entry point)
{
    const int age = 25;
    const int day = 25;

    //printf("Hello World 1 \n"); // print format (문자제어), 문자열 출력이기 때문이 ""사이에 넣어야 한다.
    printf("%s의 나이는 %d 이다. 키는 %.2fcm 입니다\n",
        "홍길동", age, 178.5); // 나이하고 숫자를 같이 출력해 준다. 

    printf("Goot\rdcv\t!!"); // \b : back (t를 지우고, d를 적는다), \t : tab, \r : 커서가 맨 앞으로 이동해 글자 바뀜 
    printf("%d %o %x \n", 12, 12, 12);
    printf("%f \n", 1e6);
    printf("%.6f \n", 3.14e-5);
    printf("%.2e \n", 0.0000314);
    printf("%c", 65); //아스키 코드
    printf("%c", '1'); //아스키 코드
    printf("%s", "A");
   // printf("Hello World 2 \n");
   // printf("%d", 65); 
    // system("pause");
    return 0; // 빨간 물결이 나올경우 앞의 ;를 확인!

    // Ctrl + Shift + S : 소스파일 전체 저장

    // 번호 클릭하면 빨간 점이 생기는데, 디버그 하면 해당 줄까지만 실행
    // F10 버튼 누르면 화살표 발생 -> F10 누를때마다 아래로 이동하여 출력 한계 지정
    // 찾기에 cmd -> cd 주소 (C:\Users\rlaxo>cd C:\Users\rlaxo\Desktop\rlaoxdn\C language\Project\Debug), 디렉터리
    // 
    // GitHub 
    // 유니테스트, 순서도 그리기
}
/*
    설명을 여러줄에 넣어준다
    ㅁㄴㅇㅁㄴㅇㄴㅁㅇㅁㄴㅇ
    ㅁㄴㅇㅁㄴㅇㄴㅇㅁ
    ㅇㅁㅇㅁㄴㅇ
*/