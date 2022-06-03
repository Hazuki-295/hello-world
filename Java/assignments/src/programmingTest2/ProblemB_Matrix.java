package programmingTest2;

import java.util.Arrays;
import java.util.Scanner;

class InvalidParamException extends Exception {
    InvalidParamException() {
    }

    public void printErrorMessage() {
        System.out.println("Invalid Arguments");
    }
}

class Matrix {
    private final int row;
    private final int column;
    private int[][] matrix;

    private final int len;
    private int[] lengths;

    Matrix(int row, int column, int len) throws InvalidParamException {
        if (row <= 0 || column <= 0) {
            throw new InvalidParamException();
        }
        this.row = row;
        this.column = column;
        this.len = len;
    }

    public void setData(Scanner input) {
        matrix = new int[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                matrix[i][j] = input.nextInt();
            }
        }

        lengths = new int[len];
        for (int i = 0; i < len; i++) {
            lengths[i] = input.nextInt();
        }
    }

    public void solve() {
        StringBuilder buffer = new StringBuilder();

        for (int length : lengths) {
            // 水平
            boolean existPath_Horizontal = false;
            outer:
            for (int i = 0; i < row; i++) { // 起始行
                for (int j = 0; j < column; j++) { // 起始列
                    int sameNumber = matrix[i][j];
                    int matchCount = 0;
                    while (j + matchCount < column && matrix[i][j + matchCount] == sameNumber) { // 匹配
                        matchCount++;
                        if (matchCount == length) {
                            existPath_Horizontal = true;
                            break outer;
                        }
                    }
                }
            }

            // 竖直
            boolean existPath_Vertical = false;
            outer:
            for (int j = 0; j < column; j++) { // 起始列
                for (int i = 0; i < row; i++) { // 起始行
                    int sameNumber = matrix[i][j];
                    int matchCount = 0;
                    while (i + matchCount < row && matrix[i + matchCount][j] == sameNumber) { // 匹配
                        matchCount++;
                        if (matchCount == length) {
                            existPath_Vertical = true;
                            break outer;
                        }
                    }
                }
            }

            // 对角线
            boolean existPath_Diagonal = false;
            outer:
            for (int i = 0; i < row; i++) { // 起始行
                for (int j = 0; j < column; j++) { // 起始列
                    int sameNumber = matrix[i][j];
                    int matchCount = 0; // 主对角线
                    while (i + matchCount < row && j + matchCount < column && matrix[i + matchCount][j + matchCount] == sameNumber) { // 匹配
                        matchCount++;
                        if (matchCount == length) {
                            existPath_Diagonal = true;
                            break outer;
                        }
                    }
                    matchCount = 0; // 副对角线
                    while (i + matchCount < row && j - matchCount >= 0 && matrix[i + matchCount][j - matchCount] == sameNumber) { // 匹配
                        matchCount++;
                        if (matchCount == length) {
                            existPath_Diagonal = true;
                            break outer;
                        }
                    }
                }
            }

            if (existPath_Horizontal || existPath_Vertical || existPath_Diagonal) {
                buffer.append("Yes ");
            } else {
                buffer.append("No ");
            }
        }
        System.out.println(buffer.toString().trim());
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Matrix other) {
            if (other.row != row || other.column != column) {
                return false;
            }
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    if (matrix[i][j] != other.matrix[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        } else {
            return false;
        }
    }

    @Override
    public int hashCode() {
        return Arrays.deepHashCode(matrix);
    }

    @Override
    public String toString() {
        return Arrays.deepToString(matrix);
    }
}

public class ProblemB_Matrix {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int caseCount = 1;
        while (input.hasNext()) {
            int m = input.nextInt();
            int n = input.nextInt();
            int len = input.nextInt();

            try {
                Matrix matrix = new Matrix(m, n, len);
                matrix.setData(input);

                System.out.printf("Case %d:%n", caseCount++);
                matrix.solve();
            } catch (InvalidParamException ex) {
                ex.printErrorMessage();
            }
        }
    }
}