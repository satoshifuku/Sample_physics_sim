import numpy as np

class Parabolic:

    g = -9.80665
    def __init__(self):
        self.delta_t = 0.1

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


    def set_trajectory(self, n, offests, mat):
        for offest in offests:
            xx = np.floor(n * offest[0] + 0.5)
            yy = np.floor(n * offest[1] + 0.5)
            mat[int(xx), int(yy)] = 1


    def show_trajectory(self, __len, mat):
        m =mat.T.astype(int)
        for row in reversed(m):
            _str = "".join(row.astype(np.unicode))
            print(_str.replace("0","_").replace("1","o"))

def main():

    parab = Parabolic()

    init_v = {"speed": np.sqrt(2) * 9.80665, "rad": np.pi / 4}

    n_step = 20
    n_part = 4

    xys = np.zeros((1,2))
    v_xys = np.array([parab.polar2Cartesian(init_v['speed'], init_v['rad'])])

    print("Initial:")
    print("  Position(x,y): (",xys[0, 0], xys[0, 1], ")")
    print("  Velocity(x,y): (",np.round(v_xys[0, 0],6),
          np.round(v_xys[0, 1], 6), ")")

    # xys = np.array([parab.pos(i, v_xys[0]) for i in range(n_step)])
    # print(np.round(xys, 6)) 

    print("\ntime, x, y")
    for i in range(n_step-1):
        temp = np.array([parab.velocity(v_xys[i])])
        v_xys = np.append(v_xys, temp,axis=0)
        temp = np.array([parab.pos_delta(v_xys[-1], xys[-1])])
        xys = np.append(xys, temp,axis=0)
    
    times = np.array([[parab.delta_t * i] for i in range(n_step)])
    print(np.round(np.append(times, xys,axis=1), 6))

    print("\nShow trajectory")

    _maxi = np.array([np.floor(np.max(xys[:,0]) + 0.5),
                      np.floor(np.max(xys[:,1]) + 0.5)])
    _mini = np.array([np.floor(np.min(xys[:,0]) + 0.5),
                      np.floor(np.min(xys[:,1]) + 0.5)])

    # print("max[x,y], min[x,y]: ", _maxi, _mini)

    xy_offest = np.array([xy - _mini for xy in xys])
    # print(np.round(xy_offest, 6))

    _len = (np.full(2, n_part) * (_maxi - _mini + np.ones(2)))

    matrix = np.zeros((int(_len[0]),int(_len[1])))

    parab.set_trajectory(n_part, xy_offest, matrix)

    parab.show_trajectory(_len, matrix)


if __name__ == "__main__":
    main()
    pass
