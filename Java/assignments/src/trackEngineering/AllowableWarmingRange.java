package trackEngineering;

import java.util.Scanner;

public class AllowableWarmingRange {

    /** 曲线半径 R (单位 m) */
    private final double R;

    /** 弹性初始弯曲半波长 l_0 (单位 cm) */
    private double l_0 = 400;

    /** 线路容许弯曲矢度 f (单位 cm) */
    private final double f;

    /** 弹性初始弯曲矢度 f_0e (单位 cm) */
    private double f_0e;

    /** 塑性初始弯曲矢度 f_0p (单位 cm) */
    private final double f_0p;

    /** 等效道床阻力 Q (单位 N/cm) */
    private final double Q;

    /** 钢的弹性模量 E (单位 MPa)，常数 */
    private final double E = 2.1e5;

    /** 温度线膨胀系数 α，常数 */
    private final double alpha = 11.8e-6;

    /** 惯性矩 I_y (单位 cm^4) */
    private final double I_y;

    public AllowableWarmingRange() {
        Scanner input = new Scanner(System.in);

        System.out.println("请输入如下轨道参数：");

        /* 换算曲率 */
        System.out.print("[1] 曲线半径 R (单位 m)：");
        R = input.nextDouble();
        System.out.print("[2] 线路容许弯曲矢度 f (单位 cm)：");
        f = input.nextDouble();
        System.out.print("[3] 弹性初始弯曲矢度 f_0e (单位 cm)：");
        f_0e = input.nextDouble();
        System.out.print("[4] 塑性初始弯曲矢度 f_0p (单位 cm)：");
        f_0p = input.nextDouble();

        /* 计算 l^2 */
        System.out.print("[5] 等效道床阻力 Q (单位 N/cm)：");
        Q = input.nextDouble();
        System.out.print("[6] 惯性矩 I_y (单位 cm^4)：");
        I_y = input.nextDouble();

    }

    public void solve() {
        /* 换算曲率 */
        double R_0 = Math.pow(l_0, 2) / (8 * f_0p);
        double reciprocalOfR_prime = 1 / R_0 + 1 / (R * 1e2);

        /* 计算 l^2 */
        double item = 2 * E * 1e2 * I_y * Math.pow(Math.PI, 2); // 2·E·I_y·π^2
        double l_2 = 1 / Q * (item * reciprocalOfR_prime + Math.pow(Math.pow(item * reciprocalOfR_prime, 2)
                + (item * (Math.pow(Math.PI, 3) / 4) * (f + f_0e) * Q), 0.5));
        double l = Math.pow(l_2, 0.5);

        /* 循环直到 l 与 l_0 接近 */
        double f_0e_prime = f_0e; // 防止未初始化
        while(Math.abs(l - l_0) > 1.0) {
            l_0 = l;
            f_0e_prime = Math.pow(l_0, 2) * f_0e / Math.pow(400, 2);
            l_2 = 1 / Q * (item * reciprocalOfR_prime + Math.pow(Math.pow(item * reciprocalOfR_prime, 2)
                    + (item * (Math.pow(Math.PI, 3) / 4) * (f + f_0e_prime) * Q), 0.5));
            l = Math.pow(l_2, 0.5);
        }
        f_0e = f_0e_prime;

        /* 计算温度力 P_N */
        double P_N = (E * 1e2 * I_y * Math.pow(Math.PI, 5) * (f + f_0e) / (2 * Math.pow(l, 4)) + Q) /
                ((f + f_0e) * Math.pow(Math.PI, 3) / (4 * Math.pow(l, 2)) + reciprocalOfR_prime);

        /* 允许温度压力 [P] */
        double P_allow = P_N / 1.3; // 安全系数 K 为 1.3

        /* 允许的升温幅度 [Δt_c] */
        double F = 77.45; // 断面积 F(cm^2)
        double delta_t_c = P_allow / (2 * E * 1e2 * F * alpha);

        /* 输出计算结果 */
        System.out.println();
        System.out.println("计算结果如下：");
        System.out.printf("[1] 换算曲率 1/R' = %f (cm^-1) \n", reciprocalOfR_prime);
        System.out.printf("[2] 最后计算得 f_0e = %.4f (cm), l = %.1f (cm) \n", f_0e, l);
        System.out.printf("[3] 计算温度力 P_N = %.1f (N) \n", P_N);
        System.out.printf("[4] 允许温度压力 [P] = %.1f (N) \n", P_allow);
        System.out.printf("[5] 允许的升温幅度 [Δt_c] = %.2f (°C) \n", delta_t_c);
    }

    public static void main(String[] args) {
        AllowableWarmingRange obj = new AllowableWarmingRange();
        obj.solve();
        // 示例输入 R(m) f(cm) f_0e(cm) f_0p(cm) Q(N/cm) I_y(cm^4)
        // 课本 P210 算例：2000 0.2 0.3 0.3 79 524
        // 课设数据：800 0.2 0.25 0.25 84 524
    }
}
