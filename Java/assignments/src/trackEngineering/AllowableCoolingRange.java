package trackEngineering;

import java.util.Scanner;

public class AllowableCoolingRange {

    /** 钢轨支座刚度 D (单位 N/mm) */
    private final double D;

    /** 轨枕间距 a (单位 mm) */
    private final double a;

    /** 钢的弹性模量 E (单位 MPa)，常数 */
    private final double E = 2.1e5;

    /** 惯性矩 I_x (单位 cm^4) */
    private final double I_x;

    /** 轮重 P_0i (单位 kN) */
    private final double P_0i;

    /** 轮距 x_i (单位 mm) */
    private final double x_i;

    /** DF_11内燃机车运行速度 v (单位 km/h) */
    private final double v;

    /** 横向水平力系数 f */
    private final double f;

    /** 轨底截面模量 W_底 (单位 cm^3) */
    private final double W_底;

    /** 钢轨屈服强度 σ_s (单位 MPa) */
    private final double sigma_s;

    public AllowableCoolingRange() {
        Scanner input = new Scanner(System.in);

        System.out.println("请输入如下轨道参数：");

        /* 计算刚比系数 k (单位 mm^-1) */
        System.out.print("[1] 钢轨支座刚度 D (单位 N/mm)：");
        D = input.nextDouble();
        System.out.print("[2] 轨枕间距 a (单位 mm)：");
        a = input.nextDouble();
        System.out.print("[3] 惯性矩 I_x (单位 cm^4)：");
        I_x = input.nextDouble();

        /* 计算最大静弯矩 M_0 */
        System.out.print("[4] 轮重 P_0i (单位 kN)：");
        P_0i = input.nextDouble();
        System.out.print("[5] 轮距 x_i (单位 mm)：");
        x_i = input.nextDouble();

        /* 计算最大动弯矩 M_d (单位 N · mm) */
        System.out.print("[6] DF_11内燃机车运行速度 v (单位 km/h)：");
        v = input.nextDouble();
        System.out.print("[7] 横向水平力系数 f ：");
        f = input.nextDouble();
        System.out.print("[8] 轨底截面模量 W_底 (单位 cm^3)：");
        W_底 = input.nextDouble();

        /* 计算允许的降温幅度 */
        System.out.print("[9] 钢轨屈服强度 σ_s (单位 MPa)：");
        sigma_s = input.nextDouble();
    }

    public void solve() {
        /* 计算刚比系数 k (单位 mm^-1) */
        double u = D / a;
        double k = Math.pow(u / (4 * E * I_x * 1e4), 0.25);

        /* 计算最大静弯矩 M_0 (单位 N · mm) */
        double[] x1 = {0, x_i, 2 * x_i}; // 第一轮位邻轮坐标
        double[] x2 = {-x_i, 0, x_i};    // 第二轮位邻轮坐标
        double M1, M2;                   // 两轮位各自的静弯矩值
        double sum1 = 0, sum2 = 0;       // 各自的求和项
        for (int i = 0; i < x1.length; i++) {
            sum1 += P_0i * 1e3 * Math.exp(-k * x1[i]) * (Math.cos(k * x1[i]) - Math.sin(k * x1[i]));
            sum2 += P_0i * 1e3 * Math.exp(-k * x2[i]) * (Math.cos(k * x2[i]) - Math.sin(k * x2[i]));
        }
        M1 = 1 / (4 * k) * sum1;
        M2 = 1 / (4 * k) * sum2;
        double M_0 = Math.max(M1, M2); // 最大静弯矩 M_0

        /* 计算最大动弯矩 M_d (单位 N · mm) */
        if (v <= 120 || v > 160) {
            System.out.println("Error: 速度 v 不在区间 (120, 160] 内");
            System.exit(1);
        }
        double alpha = 0.4 * 120 / 100;         // 速度系数 α
        double alpha_1 = 0.3 * (v - 120) / 100; // 附加速度系数 α_1
        final double beta = 0.002 * 75;         // 偏载系数 β
        double M_d = ((1 + alpha) * (1 + alpha_1) + beta) * f * M_0;

        /* 计算钢轨动弯应力 sigma_d */
        double sigma_d = M_d / (W_底 * 1e3);

        /* 计算允许的降温幅度 */
        final double sigma_f = 10;     // 钢轨附加应力，取 10 MPa
        final double alpha_ = 11.8e-6; // 温度线膨胀系数
        double delta_t_d = (sigma_s / 1.3 - sigma_d - sigma_f) / (E * alpha_); // 允许的降温幅度，安全系数 K 取 1.3

        /* 输出计算结果 */
        System.out.println();
        System.out.println("计算结果如下：");
        System.out.printf("[1] 刚比系数 k = %.7f (mm^-1) \n", k);
        System.out.printf("[2] 最大静弯矩 M_0 = %.0f (N · mm) \n", M_0);
        System.out.printf("[3] 最大动弯矩 M_d = %.0f (N · mm) \n", M_d);
        System.out.printf("[4] 钢轨动弯应力 σ_d = %.2f (MPa) \n", sigma_d);
        System.out.printf("[5] 允许的降温幅度 [Δt_d] = %.2f (°C) \n", delta_t_d);
    }

    public static void main(String[] args) {
        AllowableCoolingRange obj = new AllowableCoolingRange();
        obj.solve();
        // 示例输入 D(N/mm) a(mm) I_x(cm^4) P_0i(kN) x_i(mm) v(km/h) f W_底(cm^3) σ_s(MPa)
        // 30100 600 3217 112.8 2000 160 1.45 396 457
    }
}
