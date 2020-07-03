// You need a option "-lm" to compile on ubuntu

#include <stdio.h>
#include <math.h>

struct vector
{
    float x;
    float y;
};

float g = -9.80665;
float delta_t = 0.1;

// Initial speed and direction(radian)
float init_v = sqrtf(2) * 9.80665;
float rad = M_PI / 4;


void pos(float t, struct vector v_xy, struct vector* pp_xy){
    pp_xy->x = v_xy.x * t;
    pp_xy->y = 0.5 * g * t * t + v_xy.y * t;
}

void velocity(float dt, struct vector v_xy, struct vector* pv_xy){
    pv_xy->x = v_xy.x;
    pv_xy->y = v_xy.y + g * dt;
}

void pos_delta(float dt, struct vector v_xy,struct vector xy, struct vector* pxy){
    pxy->x = xy.x + v_xy.x * delta_t;
    pxy->y = xy.y + v_xy.y * delta_t;
}


struct vector decomposition(float v, float r){
    struct vector t;

    t.x = v * cosf(r);
    t.y = v * sinf(r);

    return t;
}

int main(int argc, char *argv[]) {
    int n = 20;

    // 
    struct vector xy[n];
    struct vector v_xy[n];

    xy[0].x = xy[0].y = 0.0;

    v_xy[0] = decomposition(init_v, rad);

    printf("Initial:\n");
    printf("  Position(x,y): (%f, %f) \n",xy[0].x,xy[0].y);
    printf("  Velocity(x,y): (%f, %f) \n\n",v_xy[0].x,v_xy[0].y);

    // for (int i = 0;i < n;i++){
    //     pos(i*delta_t,init_v_xy, &xy[i]);
    // }    

    for (int i = 0;i < n-1;i++){
        velocity(delta_t, v_xy[i], &v_xy[i+1]);
        pos_delta(delta_t, v_xy[i+1], xy[i], &xy[i+1]);
    }    

    printf("time, x, y:\n");
    for (int i = 0;i < n;i++){
        printf("%.2f, %f, %f\n",delta_t*i, xy[i].x,xy[i].y);        
    }    

    return 0;
}