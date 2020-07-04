import java.util.Arrays;
import java.lang.Math;

class Physics_show{

    public static void main(String[] args){
        Physics ph = new Physics();

        double xys[][] = new double[ph.n_step][2];
        double v_xys[][] = new double[ph.n_step][2];

        System.out.println();      
        v_xys[0] = ph.polar2Cartesian();
            
        System.out.println("Initial:");
        System.out.printf("  Position(x,y): (%.6f, %.6f)\n",xys[0][0],xys[0][1]);
        System.out.printf("  Velocity(x,y): (%.6f, %.6f)\n",v_xys[0][0],v_xys[0][1]);

        System.out.println("\ntime, x, y");
        // for(int i=0; i<ph.n_step;i++)
        //     System.out.printf("%.2f, %.6f, %.6f\n",i*ph.delta_t, ph.pos(i, v_xys[0])[0], ph.pos(i, v_xys[0])[1]);
            
        for (int i=0; i<ph.n_step-1;i++){
            double temp[] = ph.velocity(v_xys[i]);
            v_xys[i+1] = temp;
            temp = ph.pos_delta(v_xys[i+1], xys[i]);
            xys[i+1] = temp;
        }

        for (int i=0; i<ph.n_step;i++){
            System.out.printf("%.2f, %.6f, %.6f\n",i*ph.delta_t,xys[i][0],xys[i][1]);
        }

        System.out.println("\nShow trajectory");

        
        double _maxd[] = ph.max_vectors(xys);
        int _maxi[] = {(int)Math.floor(_maxd[0] + 0.5), (int)Math.floor(_maxd[1] + 0.5)};
        double _mind[] = ph.min_vectors(xys);
        int _mini[] = {(int)Math.floor(_mind[0] + 0.5), (int)Math.floor(_mind[1] + 0.5)};
        // System.out.println(Arrays.toString(_maxi));
        // System.out.println(Arrays.toString(_mini));

        double xy_offest[][] = new double[ph.n_step][2];
        for (int i=0; i<ph.n_step;i++){
            xy_offest[i][0] = xys[i][0] - _mini[0];
            xy_offest[i][1] = xys[i][1] - _mini[1];
        }

        int _len[] = {ph.n_part * (_maxi[0] - _mini[0] + 1), 
                         ph.n_part * (_maxi[1] - _mini[1] + 1)};

        int matrix[][] = new int[_len[1]][_len[0]];

        ph.set_trajectory(xy_offest, matrix);

        ph.show_trajectory(_len, matrix);

    }
}