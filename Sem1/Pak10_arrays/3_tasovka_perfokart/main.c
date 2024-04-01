#include <stdio.h>
#include <stdlib.h>

#define    RINGBUFFER_ERR_EMPTY    0
#define    INT_SIZE                (sizeof(int))
#define    FROM_RIGHT              0x08
#define    FROM_BOTTOM             0x04
#define    TO_RIGHT                0x02
#define    TO_BOTTOM               0x01


typedef struct RingBuffer{
    int len;

    int *beg,
        *end,
        *bottom,
        *top;
} RingBuffer;

char            convert_from_hex_to_dec (char src);

RingBuffer*     create_RingBuffer       (unsigned int el_num, char sign);
int             rb_take_bottom          (RingBuffer *buf);
int             rb_take_top             (RingBuffer *buf);
void            rb_add_bottom           (RingBuffer *buf, int new);
void            rb_add_top              (RingBuffer *buf, int new);
void            RingBuffer_step         (RingBuffer* left, RingBuffer* right, unsigned int op);
void            RingBuffer_shuffle      (FILE *in, RingBuffer *foo, RingBuffer *bar, int turns);
void            rb_flush                (FILE *out, RingBuffer *buf);

char convert_from_hex_to_dec(char src){
    if(src >= '0' && src <= '9'){
        return src - '0';
    }

    else{
        return 10 + src - 'A';
    }
}

RingBuffer* create_RingBuffer(unsigned int el_num, char sign){
    unsigned int len = 2*el_num + 1;

    int* arr = calloc(len, INT_SIZE);

    for(int i = 0; i < el_num; i++){
        arr[i] = (i+1)*sign;
    }

    RingBuffer* rb = calloc(1, sizeof(RingBuffer));
    rb->len = el_num;
    rb->beg = arr;
    rb->end = arr+len-1;
    rb->top = arr;
    rb->bottom = arr+el_num-1;

    return rb;
}

int rb_take_bottom(RingBuffer *buf){
    if((*buf->bottom) == 0) return RINGBUFFER_ERR_EMPTY;

    int res = *(buf->bottom);
    buf->len--;
    *(buf->bottom) = 0;

    if(buf->bottom == buf->beg){
        buf->bottom = buf->end;
    }

    buf->bottom--;

    return res;
}

int rb_take_top(RingBuffer *buf){
    if((*buf->bottom) == 0) return RINGBUFFER_ERR_EMPTY;

    int res = *(buf->top);
    buf->len --;
    *(buf->top) = 0;

    buf->top++;

    if(buf->top == buf->end){
        buf->top = buf->beg;
    }

    return res;
}

void rb_add_bottom(RingBuffer *buf, int new){
    buf->bottom++;

    if(buf->bottom == buf->end){
        buf->bottom = buf->beg;
    }

    buf->len ++;

    *(buf->bottom) = new;
}

void rb_add_top(RingBuffer *buf, int new){
    if(buf->top == buf->beg) {
        buf->top = buf->end;
    }

    buf->len ++;

    buf->top --;

    *(buf->top) = new;
}

void RingBuffer_step(RingBuffer* left, RingBuffer* right, unsigned int op){
    int temp;
    if(op == 0 || op == 10 || op == 15 || op == 5) return;

    if(FROM_RIGHT & op){
        if(FROM_BOTTOM & op){
            temp = rb_take_bottom(right);
        }
        else{
            temp = rb_take_top(right);
        }
    }
    else{
        if(FROM_BOTTOM & op){
            temp = rb_take_bottom(left);
        }
        else{
            temp = rb_take_top(left);
        }
    }

    if(temp == RINGBUFFER_ERR_EMPTY) return;
    if(TO_RIGHT & op){
        if(TO_BOTTOM & op){
            rb_add_bottom(right, temp);
        }
        else{
            rb_add_top(right, temp);
        }
    }
    else{
        if(TO_BOTTOM & op){
            rb_add_bottom(left, temp);
        }
        else{
            rb_add_top(left, temp);
        }
    }
}

void RingBuffer_shuffle(FILE *in, RingBuffer *foo, RingBuffer *bar, int turns){
    for(int i = 0; i < turns; i++){
        char operation;
        fscanf(in, "%c", &operation);
        operation = convert_from_hex_to_dec(operation);
        RingBuffer_step(foo, bar, operation);
    }
}

void rb_flush(FILE *out, RingBuffer *buf){
    fprintf(out, "%d ", buf->len);
    if(buf->len != 0) {
        while (buf->top != buf->bottom) {
            fprintf(out, "%d ", *(buf->top));
            buf->top++;
            if (buf->top == buf->end) buf->top = buf->beg;
        }
        fprintf(out, "%d ", *(buf->top));
    }
    /*fprintf(out, "%d ", buf->len);

    if(buf->len == 0){
        fprintf(out, "\n");
        return;
    }
    unsigned long long  consecutive_len,
                        jump_len;
    if(buf->bottom > buf->top){
        consecutive_len = buf->bottom - buf->top + 1;
        jump_len = 0;
    }
    else{
        consecutive_len = buf->end - buf->top;
        jump_len = buf->bottom - buf->beg + 1;
    }

    for(int i = 0; i < consecutive_len; i++){
        fprintf(out, "%d ", *(buf->top + i));
    }
    buf->top = buf->beg;
    for(int i = 0; i < jump_len; i++){
        fprintf(out, "%d ", *(buf->top + i));
    }*/

    fprintf(out, "\n");
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");
    int deck_len,
        shuffle_len;
    fscanf(fi, "%d %d\n", &deck_len, &shuffle_len);
    RingBuffer  *l = create_RingBuffer(deck_len, 1),
                *r = create_RingBuffer(deck_len, -1);
    RingBuffer_shuffle(fi, l, r, shuffle_len);
    rb_flush(fo, l);
    rb_flush(fo, r);
    fclose(fi);
    fclose(fo);
    return 0;
}