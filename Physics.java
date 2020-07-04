import java.util.Arrays;
import java.lang.Math;

class Physics{
    double g;
    double delta_t;
    public double speed;
    public double rad;

    public int n_step;
    public int n_part;

    public Physics(){
      g = -9.80665;
      delta_t = 0.1;
      speed = Math.sqrt(2) * 9.80665;
      rad = Math.PI / 4.0;

      n_step = 20;
      n_part = 4;

    }

    public double[] polar2Cartesian(){
        double data[] = {speed * Math.cos(rad), speed * Math.sin(rad)};
        return data;
    }

    public double[] pos(int count, double velocity[]){
        double t = count * delta_t;
        double data[] = {velocity[0] * count * delta_t, 
                0.5 * g * t * t + velocity[1] * t};
        return data;
    }

    public double[] velocity(double v_xy[]){
        double data[] = {v_xy[0], v_xy[1] + g * delta_t};
        return data;
    }

    public double[] pos_delta(double v_xy[],double xy[]){
        double data[] = {xy[0] + v_xy[0] * delta_t, xy[1] + v_xy[1] * delta_t};
        return data;
    }

    public double[] max_vectors(double array[][]){
        double _max[] = array[0].clone();
        for (int i = 1; i < n_step; i++) {
            if (array[i][0] > _max[0])
                _max[0] = array[i][0];
            if (array[i][1] > _max[1])
                _max[1] = array[i][1];
        }
        return _max;
    }

    public double[] min_vectors(double array[][]){
        double _min[] = array[0].clone();
        for (int i = 1; i < n_step; i++) {
            if (array[i][0] < _min[0])
                _min[0] = array[i][0];
            if (array[i][1] < _min[1])
                _min[1] = array[i][1];
        }
        return _min;
    }

    public void set_trajectory(double offest[][], int mat[][]){
        // System.out.printf("%d, %d\n",mat.length, mat[0].length);  
        for(int i =0;i<n_step;i++){
            int xx = (int)Math.floor(n_part*(offest[i][0])+0.5);
            int yy = (int)Math.floor(n_part*(offest[i][1])+0.5);
            mat[yy][xx] = 1;
        }
    }


    public void show_trajectory(int len[], int mat[][]){

        for (int yi = len[1]-1;yi >= 0;yi--){
            for (int xi = 0;xi < len[0];xi++){
                // System.out.printf("",mat[yi][xi]);
                if (mat[yi][xi] == 0) System.out.printf("_");
                else System.out.printf("o");
            }
            System.out.printf("\n");        
        }

    }

}