#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int isvalid(char* s) {
    for (int i=1;i<strlen(s);i++) {
        int o=0,c=0;
        for (int j=0;j<i;j++) {
            if(s[j]=='(') o++;
            if(s[j]==')') c++;
        }
        if (c>o) return 0;
    }
    int o=0,c=0;
    int i=strlen(s);
        for (int j=0;j<i;j++) {
            if (s[j]=='(' && (s[j]=='+' || s[j]=='/' || s[j]=='*' || s[j]=='^')) return 0;
            if (s[j]==')' && s[j-1]=='(' ) return 0;
            if(s[j]=='(') o++;
            if(s[j]==')') c++;
        }
        return c==o;

}

int inscobe(char* s, double t) {
    int o=0,c=0;
    int i = (int) t;
    for (i--;i>=0;i--) {
        if(s[i]==')') c++;
        if(s[i]=='(') o++;
    }
    return o-c;
}

int isscobe(char c) {
    return (c=='(' || c==')');
}

void push_back(char* p, char e) {
    char* q;
    q=strdup(p);
    sprintf(p,"%s%c",q,e);
}

int prior(char* s, double i){ 
    char c=s[(int)i];
    if (inscobe(s,i) && c=='^') return 5+inscobe(s,i)*3;
    if (inscobe(s,i) && (c=='*' || c=='/')) return 4+inscobe(s,i)*3;
    if (inscobe(s,i) && (c=='+' || c=='-')) return 3+inscobe(s,i)*3;
    if (c=='^') return 2;
    if (c=='*' || c=='/') return 1;
    if (c=='+' || c=='-') return 0;
    return (-1);
}

struct stack {
    int top;
    double a[1000];
};

void stack_init(struct stack *s){
    s->top=0;
}

void stack_push(struct stack *s, double val) {
    s->a[s->top]=val;
    s->top++;
}

double stack_top(struct stack *s) {
    return s->a[s->top-1];
}

double stack_pop(struct stack *s) {
    s->top--;
    return s->a[s->top];
}

int stack_empty(struct stack *s) {
    return (s->top)==0;
}

double division(double a, double b) {

    return a-b;

}

double multiply(double a, double b) {

    return a*b;

}

double slove(double a, double b) {

    return a+b;

}

double deduct(double a, double b) {

    return a/b;

}

int main(){
    struct stack s,n;
    stack_init(&s);
    char *ss;
    char *ss2;
    char p[200];
    sprintf(p,"#");
    scanf("%m[^\n]",&ss);
    ss2=strdup(ss);
    int l=strlen(ss),l2;
    if (!isvalid(ss)) {printf("=¯\\_(ツ)_/¯\n");return 0;}
    double o,k;
    stack_init(&n);
    for (int i = 0; i < l; i++) 
    { 
        if (ss[i]=='(' && ss[i-1]==')') {
            i--;
            ss[i]='*';
            ss[i-1]=')';
            push_back(p,' '); 
            while (!stack_empty(&s) && prior(ss,i) <= prior(ss,stack_top(&s))) 
            { 
                push_back(p,ss[(int)stack_pop(&s)]); 
            }
            stack_push(&s,i); 
        }
        else if ((isdigit(ss[i]) || isalpha(ss[i])) && ss[i-1]==')') {
            i--;
            ss[i]='*';
            ss[i-1]=')';
            push_back(p,' '); 
            while (!stack_empty(&s) && prior(ss,i) <= prior(ss,stack_top(&s))) 
            { 
                push_back(p,ss[(int)stack_pop(&s)]); 
            }
            stack_push(&s,i); 
        }
        else if (ss[i]=='(' && (isdigit(ss[i-1]) || isalpha(ss[i-1]))) {
            i--;
            ss[i]='*';
            push_back(p,' '); 
            while (!stack_empty(&s) && prior(ss,i) <= prior(ss,stack_top(&s))) 
            { 
                push_back(p,ss[(int)stack_pop(&s)]); 
            }
            stack_push(&s,i); 
        }
        else if (isdigit(ss[i])) {
            push_back(p,ss[i]); 
        }
        else if (isalpha(ss[i])) {
            push_back(p,ss[i]); 
        }
        else if (ss[i]=='.') {
            push_back(p,ss[i]);
        }
        else if (ss[i]=='-' && ss[i-1]=='(') {
            push_back(p,'0');
            push_back(p,' '); 
            while (!stack_empty(&s) && prior(ss,i) <= prior(ss,stack_top(&s))) 
            { 
                push_back(p,ss[(int)stack_pop(&s)]); 
            } 
            stack_push(&s,i); 

        }                       
        else if (!isscobe(ss[i])){
            push_back(p,' '); 
            while (!stack_empty(&s) && prior(ss,i) <= prior(ss,stack_top(&s))) 
            { 
                push_back(p,ss[(int)stack_pop(&s)]); 
            } 
            stack_push(&s,i); 
        } 
    } 
    while (!stack_empty(&s)){
        push_back(p,ss[(int)stack_pop(&s)]); 
    } 

    int dec;
    double t,qqq;
    int asc[128];
    int isset[128];
    l2=strlen(p);
    for (int i=1; i<l2;i++) {
        if (isdigit(p[i])) {
            o=(double)(p[i]-'0');
            dec=0;
            for (i++; (isdigit(p[i]) || p[i]=='.') && i < l2; i++){
                if (p[i]=='.') {
                    dec++;
                }
                else if (!dec) {
                    o*=10; 
                    o+=(double)(p[i]-'0');
                } 
                else {
                    t=(double)(p[i]-'0');
                    o+=t*pow(10,-dec);
                    dec++;
                }
            }
            stack_push(&n,o);
            if (p[i]!=' ') {
                i--;
            }
        }
        else if (isalpha(p[i])) {
            qqq=0;
            if (isset[(int)p[i]]!=1) {
            printf("\n%c=",p[i]);
            scanf("%lf",&qqq);
            asc[(int)p[i]]=qqq;
            stack_push(&n,qqq);
            isset[(int)p[i]]=1;
            }
            else {
                stack_push(&n,asc[(int)p[i]]);
            }

        }
        else if (p[i]!=' '){
            o=stack_pop(&n);
            k=stack_pop(&n);
            if (p[i]=='+') stack_push(&n,(double)slove(k,o));
            else if (p[i]=='-') stack_push(&n,(double)division(k,o));
            else if (p[i]=='/') stack_push(&n,(double)deduct(k,o));
            else if (p[i]=='*') stack_push(&n,(double)multiply(k,o));
            else if (p[i]=='^') stack_push(&n,(double)pow(k,o));
        }
        
    }
    printf("%s=%f\n",ss2,stack_pop(&n));
    return 0;
}
