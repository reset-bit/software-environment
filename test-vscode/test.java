import java.io.*;
import java.util.*;

class Student implements Serializable {
    private static final long serialVersionUID = 1L;
    private int no;
    private String name;
    private String course;
    private int score;

    public Student(int no, String name, String course, int score) {
        this.no = no;
        this.name = name;
        this.course = course;
        this.score = score;
    }

    @Override
    public String toString() {
        return "no:" + no +
                ", name: '" + name + '\'' +
                ", course: '" + course + '\'' +
                ", score: " + score;
    }
}

public class test {

    private static List<Student> students;
    private static String filePath;

    private static void printMenu() {
        System.out.println("=====================================");
        System.out.println("请输入操作选择：");
        System.out.println("1. 杈撳叆骞朵繚瀛樻暟鎹�?");
        System.out.println("2. 浠庣鐩樿鍏ユ暟鎹�?");
        System.out.println("3. 閫€鍑�");
        System.out.println("=====================================");
        System.out.println("\n");
    }

    private static void readFromConsole(Scanner sc) {
        System.out.println("璇疯緭鍏ュ鐢熶俊鎭紝 姣忚鏍煎紡锛氬鍙�? 濮撳�? 閫変慨璇剧▼ 璇剧▼鎴愮哗");
        System.out.println("渚嬶�? 202001010001 寮犱�? Java绋嬪簭璁捐 100");
        System.out.println("杈撳叆绌鸿缁撴潫銆�?");

        while (sc.hasNextLine()) {
            String s = sc.nextLine();

            if (s.equals("")) {
                break;
            }
            int no, score;
            String name, course;
            try {
                String[] data = s.split(" ");
                no = Integer.parseInt(data[0]);
                name = data[1];
                course = data[2];
                score = Integer.parseInt(data[3]);
            } catch (IndexOutOfBoundsException e) { // 涓嬫爣鍑洪敊涓烘牸寮忔湁璇�
                System.out.println("鏍煎紡鏈夎, 璇烽噸鏂拌緭鍏ャ€俓n\n");
                return;
            }
            Student stu = new Student(no, name, course, score);
            students.add(stu);
        }
    }

    private static void readFromFile() {
        ObjectInputStream oi = null;
        try {
            File file = new File(filePath);
            oi = new ObjectInputStream(new FileInputStream(file));
            int len = oi.readInt();
            for (int i = 0; i < len; i++) {
                students.add((Student) oi.readObject());
            }
        } catch (FileNotFoundException e) {
            System.out.println(filePath + " 鏂囦欢鏈壘鍒般€�");
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        } catch (ClassNotFoundException e) {
            System.out.println(filePath + " 鏂囦欢鏍煎紡閿欒銆�?");
            e.printStackTrace();
            System.exit(1);
        } finally {
            try {
                oi.close();
            } catch (IOException e) {
                System.out.println("鏂囦欢璇诲彇鏃跺叧闂け璐ャ€�");
                System.exit(1);
            }
        }
    }

    private static void writeToFile() {
        ObjectOutputStream oo = null;
        try {
            File file = new File(filePath);
            if (!file.exists()) { // 鏂囦欢涓嶅瓨鍦ㄦ椂鍒涘缓鏂版枃浠�?
                file.createNewFile();
            }
            oo = new ObjectOutputStream(new FileOutputStream(file));
            /*
                鏂囦欢鏍煎紡: 绗竴浣岻nt琛ㄧず鎺ヤ笅鏉ョ殑Student瀵硅薄涓暟锛� 鎺ヤ笅鏉ヤ负瀵瑰簲涓暟鐨凷tudent瀵硅�?
             */
            oo.writeInt(students.size());
            for (Student s : students) {
                oo.writeObject(s);
            }
        } catch (IOException e) {
            System.out.println("鏂囦欢鍐欏叆澶辫触銆�?");
            e.printStackTrace();
            System.exit(1);
        } finally {
            try {
                oo.close();
            } catch (IOException e) {
                System.out.println("鏂囦欢鍐欏叆鏃跺叧闂け璐ャ€�");
                e.printStackTrace();
                System.exit(1);
            }
        }
    }

    private static void printStudentsInfo() {
        System.out.println("瀛︾敓鎴愮哗淇℃伅濡備笅锛� ");
        for (Student s : students) {
            System.out.println(s.toString());
        }
        System.out.println("");
    }

    public static void main(String[] args) {
        filePath = "d:\\data.dat";
        if (args.length > 1) { // 鍙傛暟涓烘枃浠惰矾寰�?
            filePath = args[1];
        }
        Scanner sc = new Scanner(System.in);
        students = new ArrayList<Student>();
        while (true) {
            students.clear();
            printMenu();
            String op = sc.nextLine();
            if (op.equals("1")) {
                readFromConsole(sc);
                writeToFile();
                System.out.println("鏂囦欢鍐欏叆鎴愬姛銆�?");
            } else if (op.equals("2")) {
                readFromFile();
                printStudentsInfo();
                System.out.println("鎸夊洖杞﹂敭缁х画 ...");
                sc.nextLine();
            } else if (op.equals("3")) {
                break;
            } else {
                System.out.println("鏃犳晥鐨勮緭鍏ャ€俓n\n");
            }
        }
        sc.close();
    }
}

