// You need a option "-lm" to compile on ubuntu

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct vectori
{
    int x;
    int y;
};

struct vectorf
{
    float x;
    float y;
};

float g = -9.80665;
float delta_t = 0.1;

// Initial speed and direction(radian)
float speed = sqrtf(2) * 9.80665;
float rad = M_PI / 4;

int n_step = 20;
int n_part = 4;


void pos(float t, struct vectorf v_xy, struct vectorf* pp_xy){
    pp_xy->x = v_xy.x * t;
    pp_xy->y = 0.5 * g * t * t + v_xy.y * t;
}

void velocity(float dt, struct vectorf v_xy, struct vectorf* pv_xy){
    pv_xy->x = v_xy.x;
    pv_xy->y = v_xy.y + g * dt;
}

void pos_delta(float dt, struct vectorf v_xy,struct vectorf xy, struct vectorf* pxy){
    pxy->x = xy.x + v_xy.x * delta_t;
    pxy->y = xy.y + v_xy.y * delta_t;
}


struct vectorf Polar2Cartesian(float v, float r){
    struct vectorf t;

    t.x = v * cosf(r);
    t.y = v * sinf(r);

    return t;
}

struct vectorf max_vectors(int len, struct vectorf* array){
    struct vectorf _max = array[0];
    for (int i = 1; i < len; i++) {
        if (array[i].x > _max.x)
            _max.x = array[i].x;
        if (array[i].y > _max.y)
            _max.y = array[i].y;
    }

    return _max;
}

struct vectorf min_vectors(int len, struct vectorf* array){
    struct vectorf _min = array[0];
    for (int i = 1; i < len; i++) {
        if (array[i].x < _min.x)
            _min.x = array[i].x;
        if (array[i].y < _min.y)
            _min.y = array[i].y;
    }

    return _min;
}

void slide_xy_by_min(int min_x, int min_y, struct vectorf* _xy, struct vectorf* xy_offest){
    for(int i =0;i<n_step;i++){
        xy_offest[i].x = _xy[i].x- min_x;
        xy_offest[i].y = _xy[i].y- min_y;
    }

}

void make_matrix(int len_x, int len_y, int mat[len_y][len_x]){
    for (int yi = 0;yi < len_y;yi++){
        for (int xi = 0;xi < len_x;xi++){
            mat[yi][xi] = 0;
        }
    }

}

void set_trajectory(struct vectorf offest[], int len_x, int len_y, int matrix[len_y][len_x]){
    for(int i =0;i<n_step;i++){
        int xx = floorf(n_part*(offest[i].x)+0.5);
        int yy = floorf(n_part*(offest[i].y)+0.5);
        matrix[yy][xx] = 1;
    }
}


void show_trajectory(int len_x, int len_y, int mat[len_y][len_x]){

    for (int yi = len_y-1;yi >= 0;yi--){
        // printf("%d \t",yi);
        for (int xi = 0;xi < len_x;xi++){
            if (mat[yi][xi] == 0) printf("_");
            else printf("o");
        }
        printf("\n");        
    }

}

int main(int argc, char *argv[]) {


    // 
    struct vectorf xy[n_step];
    struct vectorf v_xy[n_step];

    struct vectorf xy_offest[n_step];

    xy[0].x = xy[0].y = 0.0;

    v_xy[0] = Polar2Cartesian(speed, rad);

    printf("Initial:\n");
    printf("  Position(x,y): (%f, %f) \n",xy[0].x,xy[0].y);
    printf("  Velocity(x,y): (%f, %f) \n\n",v_xy[0].x,v_xy[0].y);

    // for (int i = 0;i < n_step;i++){
    //     pos(i*delta_t,init_v_xy, &xy[i]);
    // }    

    for (int i = 0;i < n_step-1;i++){
        velocity(delta_t, v_xy[i], &v_xy[i+1]);
        pos_delta(delta_t, v_xy[i+1], xy[i], &xy[i+1]);
    }    

    printf("time, x, y:\n");
    for (int i = 0;i < n_step;i++){
        printf("%.2f, %f, %f\n",delta_t*i, xy[i].x,xy[i].y);        
    }

    printf("\nShow trajectory\n");
    
    struct vectorf _maxf = max_vectors(n_step, xy);
    struct vectorf _minf = min_vectors(n_step, xy);    

    struct vectori _maxi = {floorf(_maxf.x + 0.5f), floorf(_maxf.y + 0.5f)};
    struct vectori _mini = {floorf(_minf.x + 0.5f), floorf(_minf.y + 0.5f)};    

    // printf("\nMax(x,y): (%d, %d), Min(x,y): (%d, %d)\n",_maxi.x, _maxi.y, _mini.x, _mini.y);

    slide_xy_by_min(_mini.x, _mini.y, xy, xy_offest);

    struct vectori len = {n_part * (_maxi.x - _mini.x + 1), 
                          n_part * (_maxi.y - _mini.y + 1)};

    int (*matrix)[len.x] = malloc(sizeof(int) * len.x * len.y);

    make_matrix(len.x, len.y, matrix);

    set_trajectory(xy_offest, len.x, len.y, matrix);
    
    show_trajectory(len.x, len.y, matrix);

    return 0;
}