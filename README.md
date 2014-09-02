RML
====

RML is a markup language inspired by **Diet Templates** from vibe.d, **Jade templates**, and **HAML**.

The syntax is roughly equivalent to XML with one key difference: you don't need to include closing tags - It's implicit in the structure of the code. 

This is especially useful since HTML tags come in variety of flavors:

* Tags that must have a closing tag
* Tags that must not have a closing tag
* Tags that must have a closing tag unless an arbitrary list of requirements is met.

RML also includes some simplified ways of writing common attributes like **id** and **class**.

## Outcomes

RML generates highly readable code that can be formatted with either no whitespace, spaces, or tabulators. By using the indentation structure to our advantage we can both reduce the overall work required, and also improve readability.

If a programmer were to manually write the highly structured, readable, generated code in HTML they would have to write roughly double the lines (for the closing tags). To avoid these extra lines most developers put small nodes (like **h1** and **p**) onto a single line, and reseve the verbosity for large nodes (like **div** and **form**). 

This method has worked for years, but it is tedious and error prone. Worst of all it makes the structure of the code inconsistent, which greatly hinders readability. A good editor will try to mitigate these problems as much as possible, but the problem lies in the language, not the underlying problem being solved. 

##Future Work

#### Templating

HTML often has a repetative nature to it. Certain structures are repeated again and again despite minor
changes. With templates you could define a sub-tree of html nodes and "fill-in" the blanks. With templates, the act of making a bootstrap alert-warning div could be as simple as

    alert-warning
        A really bad thing is about to happen!
        
Versus the equivalent html

    <div class="alert alert-warning">
        A really bad thing is about to happen!
    </div>

#### Framework Code

If RML is to be widely used it will need to be able to be integrated into various frameworks such as C# MVC, Spring, etc.


## Example 1

Input:

    html
        head
            title
                Page Title
        body
            h1
                Big Heading
            h2
                Smaller Heading
            p
                Paragraph!

Output (with the "spaces" option):

    <!DOCTYPE html>
    <html>
        <head>
            <title>
                Page Title
            </title>
        </head>
        <body>
            <h1>
                Big Heading
            </h1>
            <h2>
                Smaller Heading
            </h2>
            <p>
                Paragraph!
            </p>
        </body>
    </html>
    
