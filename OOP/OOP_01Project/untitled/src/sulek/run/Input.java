package sulek.run;

import java.util.Scanner;

public interface Input {
    Scanner scanner = new Scanner(System.in);
     default String input(){
        return scanner.nextLine();
    }
}
