#include <stdio.h>
#include <unistd.h>

int encoder(){
    char ans;
    while(scanf("%c",&ans) == 1){
        if((ans >= 'a' && ans <='z') || (ans >= 'A' && ans <='Z')) {
            if (ans == 'z') printf("a");
            else if (ans == 'Z') printf("A");
            else printf("%c", (char) (ans + 1));
        }else printf("%c",ans);
    }
    printf("\n");
    return 0;
}
int decoder(){
    char ans;
    while(scanf("%c",&ans) == 1){
        if((ans >= 'a' && ans <='z') || (ans >= 'A' && ans <='Z')) {
            if (ans == 'a') printf("z");
            else if (ans == 'A') printf("Z");
            else printf("%c", (char) (ans - 1));
        }else printf("%c",ans);
    }
    printf("\n");
    return 0;
}
int main(int argc, char* argv[]){
    char key;
    char* opts = "cd";
    key = getopt(argc,argv,opts);
    if(key == 'c'){
        encoder();
    }else if(key == 'd'){
        decoder();
    }else{
        printf("incorrect option\n");
        return 1;
    }
    return 0;
}