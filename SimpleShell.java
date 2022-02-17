//Henry Tse, 1030068

package javashell;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class JavaShell {

    public static void main(String[] args) throws java.io.IOException {
        String commandLine, output;
        char c1, c2;
        int pos;
        List<String> parameters = new ArrayList<>();
        List<String> history = new ArrayList<>();
        BufferedReader console = new BufferedReader(new InputStreamReader(System.in));
        
        while (true) {
            //Starts java shell
            System.out.print("jsh>");
            commandLine = console.readLine();
            commandLine = commandLine.trim();
            
            //Check for a history command
            if (commandLine.length() >= 2) {
                c1 = commandLine.charAt(0);
                c2 = commandLine.charAt(1);
                if (c1 == '!') {
                    if (c2 == '!') {
                        if (!history.isEmpty()) {
                            commandLine = history.get(history.size() - 1);
                        }
                        else {
                            System.out.println("History is empty!");
                            continue;
                        }
                    }
                    else if (c2 >= '0' && c2 <= '9') {
                        commandLine = commandLine.substring(1);
                        try {
                            pos = Integer.parseInt(commandLine);
                            commandLine = history.get(pos);
                        }
                        catch (Exception e){
                            System.out.println("Invalid Command!");
                            continue;
                        }
                    }
                    else {
                        System.out.println("Invalid Command!");
                        continue;
                    }
                }
            }
            else if (commandLine.length() == 1) {
                c1 = commandLine.charAt(0);
                if (c1 == '!') {
                    System.out.println("Invalid Command!");
                    continue;
                }
            }
            //Checks if command is empty
            else if (commandLine.equals("")) {
                continue;
            }
            
            //Adds command to the history
            history.add(commandLine);
            
            //Checks if history is requested
            if (commandLine.equalsIgnoreCase("History")) {
                for (int i = 0; i < history.size(); i++) {
                    System.out.println(i + ".) " + history.get(i));
                }
                continue;
            }
            //Checks if user wants to end program
            else if (commandLine.equalsIgnoreCase("Exit")) {
                System.exit(0);
            }
            
            //Creates parameters to run
            parameters.addAll(Arrays.asList(commandLine.split(" ")));
            
            //Runs the command
            Process proc = new ProcessBuilder(parameters).start();
            InputStream inStream = proc.getInputStream();
            InputStreamReader inRead = new InputStreamReader(inStream);
            BufferedReader buffRead = new BufferedReader(inRead);
            
            //Print command output
            while ((output = buffRead.readLine()) != null) {
                System.out.println(output);
            }
            
            //Finishes command
            parameters.clear();
            proc.destroy();
        }
    }
}
