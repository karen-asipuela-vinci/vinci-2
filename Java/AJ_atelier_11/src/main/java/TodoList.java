import java.util.ArrayList;
import java.util.List;

public class TodoList {
    private List<String> tasks = new ArrayList<>();
    public boolean add(String task1) {
        //on met isBlank() pour éviter les espaces aussi
        if (task1 == null || task1.isBlank()) {
            return false;
        }
        if(containsTask(task1)) {
            return false;
        }
        return tasks.add(task1);
    }

    public boolean containsTask(String task1) {
        if (task1 == null || task1.isBlank()) {
            return false;
        }
        return tasks.contains(task1);
    }
}
