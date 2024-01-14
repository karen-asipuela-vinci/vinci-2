package be.vinci.services;

import jakarta.json.*;

import java.lang.reflect.*;
import java.util.Arrays;

/**
 * Class analyzer. It saves a class into attribute, from a constructor, and
 * gives a lot of convenient methods to transform this into a JSON object
 * to print the UML diagram.
 */
public class ClassAnalyzer {

    private Class aClass;

    public ClassAnalyzer(Class aClass) {
        this.aClass = aClass;
    }

    /**
     * Create a JSON Object with all the info of the class.
     * @return
     */
    public JsonObject getFullInfo() {
        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
        objectBuilder.add("name", aClass.getSimpleName());
        objectBuilder.add("fields", getFields());
        objectBuilder.add("methods", getMethods());
        return objectBuilder.build();
    }

    /**
     * Get a field, and create a Json Object with all field data.
     * Example :
     * {
     * name: "firstname",
     * type: "String",
     * visibility : "private"  // public, private, protected, package
     * isStatic: false,
     * }
     */
    public JsonObject getField(Field f) {
        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
        // TODO add missing info
        objectBuilder.add("name", f.getName());
        //penser à rajouter vérif:
        if(f.getGenericType() instanceof ParameterizedType){
            objectBuilder.add("type", f.getGenericType().toString());
        } else {
            objectBuilder.add("type", f.getType().getSimpleName());
        }
        objectBuilder.add("visibility", getFieldVisibility(f));
        objectBuilder.add("isStatic", isFieldStatic(f));
        return objectBuilder.build();
    }

    /**
     * Get fields, and create a Json Array with all fields data.
     * Example :
     * [ {}, {} ]
     * This method rely on the getField() method to handle each field one by one.
     */
    public JsonArray getFields() {
        //le constructeur de Array est diff :
        JsonArrayBuilder arrayBuilder = Json.createArrayBuilder();
        // TODO Add all fields descriptions to array (use the getField() method above)
        for(Field f : aClass.getDeclaredFields()){
            arrayBuilder.add(getField(f));
        }
        return arrayBuilder.build();
    }

    /**
     * Return whether a field is static or not
     *
     * @param f the field to check
     * @return true if the field is static, false else
     */
    private boolean isFieldStatic(Field f) {
        return Modifier.isStatic(f.getModifiers()); // TODO
    }

    /**
     * Get field visibility in a string form
     *
     * @param f the field to check
     * @return the visibility (public, private, protected, package)
     */
    private String getFieldVisibility(Field f) {
        if(Modifier.isPublic(f.getModifiers())) return "public";
        if(Modifier.isPrivate(f.getModifiers())) return "private";
        if(Modifier.isProtected(f.getModifiers())) return "protected";
        //sinon c'est package :
        return "package"; // TODO
    }

    //méthodes :
    /**
     * GetMethod() and create Json object with method data
     * Example :
     *      {
     *          name: "setFirstName",
     *          returnType: null,
     *          parameters: ["String"]
     *          visibility : "public"  // public, private, protected, package
     *          isStatic: false,
     *          isAbstract: false
     *      }
     */
    private JsonObject getMethod(Method method){
        JsonObjectBuilder objectBuilder = Json.createObjectBuilder();
        objectBuilder.add("name", method.getName());
        objectBuilder.add("returnType", method.getReturnType().getSimpleName());
        objectBuilder.add("parameters", getParameters(method));
        objectBuilder.add("visibility", getVisibilityMethod(method));
        objectBuilder.add("isStatic", Modifier.isStatic(method.getModifiers()));
        objectBuilder.add("isAbstract", Modifier.isAbstract(method.getModifiers()));
        return objectBuilder.build();
    }

    private JsonArray getMethods() {
        JsonArrayBuilder arrayBuilder = Json.createArrayBuilder();
        for(Method m : aClass.getDeclaredMethods()){
            arrayBuilder.add(getMethod(m));
        }
        return arrayBuilder.build();
    }

    private String getVisibilityMethod(Method m){
        if(Modifier.isPublic(m.getModifiers())) return "public";
        if(Modifier.isPrivate(m.getModifiers())) return "private";
        if(Modifier.isProtected(m.getModifiers())) return "protected";
        //sinon c'est package :
        return "package";
    }
    /**
     * Get method parameters, and create a Json Array with the method parameters types.
     * Example :
     * [ {}, {} ]
     */
    public JsonArray getParameters(Method m) {
        JsonArrayBuilder arrayBuilder = Json.createArrayBuilder();
        for (Parameter p : m.getParameters()) {
            arrayBuilder.add(p.getType().getSimpleName());
        }
        return arrayBuilder.build();
    }
}
