import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

class Parabolic:

    g = -9.80665
    def __init__(self):
        self.delta_t = 0.01

    def pos(self, count, velocity):
        t = count * self.delta_t 
        return [velocity[0] * count * self.delta_t, 
                0.5 * self.g * t * t + velocity[1] * t]


    def velocity(self, v_xy):
        # print(v_xy[0], v_xy[1])
        return [v_xy[0], v_xy[1] + self.g * self.delta_t]


    def pos_delta(self, v_xy, xy):
        return [ xy[0] + v_xy[0] * self.delta_t, xy[1] + v_xy[1] * self.delta_t]


    def polar2Cartesian(self, speed, rad):
        return [speed * np.cos(rad), speed * np.sin(rad)]


def main():

    parab = Parabolic()

    init_v = {"speed": np.sqrt(2) * 9.80665, "rad": np.pi / 4}

    n_step = 200
    n_part = 4

    xys = np.zeros((1,2))
    v_xys = np.array([parab.polar2Cartesian(init_v['speed'], init_v['rad'])])

    print("Initial:")
    print("  Position(x,y): (",xys[0, 0], xys[0, 1], ")")
    print("  Velocity(x,y): (",np.round(v_xys[0, 0],6),
          np.round(v_xys[0, 1], 6), ")")

    # xys = np.array([parab.pos(i, v_xys[0]) for i in range(n_step)])
    # print(np.round(xys, 6)) 

    for i in range(n_step-1):
        temp = np.array([parab.velocity(v_xys[i])])
        v_xys = np.append(v_xys, temp,axis=0)
        temp = np.array([parab.pos_delta(v_xys[-1], xys[-1])])
        xys = np.append(xys, temp,axis=0)
    
    fig = plt.figure()
    plt.plot()
    plt.title('Trajectory')
    plt.xlabel('x')
    plt.ylabel('y')

    ims = []
    for step in range(n_step):
        line, = plt.plot(xys[:step,0], xys[:step,1], "r")
        ims.append([line])

    ani = animation.ArtistAnimation(fig, ims,interval=10)
    ani.save('anim.gif', writer="imagemagick")
    # ani.save('anim.mp4', writer="ffmpeg")
    plt.show()


if __name__ == "__main__":
    main()
    pass
