import java.util.ArrayList;
import java.util.List;

public class TodoList {
    private List<String> tasks = new ArrayList<>();
    public boolean add(String task1) {
        if (task1 == null || task1.isEmpty()) {
            return false;
        }
        return tasks.add(task1);
    }

    public boolean containsTask(String task1) {
        if (task1 == null || task1.isEmpty()) {
            return false;
        }
        return tasks.contains(task1);
    }
}
