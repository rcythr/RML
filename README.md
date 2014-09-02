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


## Example 1 (Contrived Example)

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
    
    
## Example 2 (Bootstrap Starter Template)

Input:

    html lang="en"
        head
            meta charset="utf-8"
            meta http-equiv="X-UA-Compatible" content="IE=edge"
            meta name="viewport" content="width=device-width, initial-scale=1"
            meta name="description" content=""
            meta name="author" content=""
    
            title
                Test 1 Page
            link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap.min.css"
        body style="padding-top: 50px;"
            div.navbar.navbar-inverse.navbar-fixed-top role="navigation"
                div.container
                    div.navbar-header
                        button.navbar-toggle.collapsed type="button" data-toggle="collapse" data-target=".navbar-collapse"
                            span.sr-only
                                Toggle navigation
                            span.icon-bar
                            span.icon-bar
                            span.icon-bar
                        a.navbar-brand href="#"
                            Project Name
                    div.collapse.navbar-collapse
                        ul.nav.navbar-nav
                            li.active
                                a href="#"
                                    Home
                            li
                                a href="#about"
                                    About
                            li
                                a href="#contact"
                                    Contact
            div.container
                div style="padding: 40px 15px; text-align: center;"
                    h1
                        Bootstrap starter template
                    p.lead
                        Use this document as a way to quickly start any new project
                        br
                        All you get is this text and a mostly barebones HTML document.
    
            script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"
            script src="https://maxcdn.boostrapcdn.com/bootstrap/3.2.0/js/boostrap.min.js"
            
Output (with "spaces" option):

    <!DOCTYPE html>
    <html lang="en">
        <head>
            <meta charset="utf-8" />
            <meta content="IE=edge" http-equiv="X-UA-Compatible" />
            <meta content="width=device-width, initial-scale=1" name="viewport" />
            <meta content name="description" />
            <meta content name="author" />
            <title>
                Test 1 Page
            </title>
            <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap.min.css" rel="stylesheet" />
        </head>
        <body style="padding-top: 50px;">
            <div class="navbar navbar-inverse navbar-fixed-top" role="navigation">
                <div class="container">
                    <div class="navbar-header">
                        <button class="navbar-toggle collapsed" data-target=".navbar-collapse" data-toggle="collapse" type="button">
                            <span class="sr-only">
                                Toggle navigation
                            </span>
                            <span class="icon-bar">
                            </span>
                            <span class="icon-bar">
                            </span>
                            <span class="icon-bar">
                            </span>
                        </button>
                        <a class="navbar-brand" href="#">
                            Project Name
                        </a>
                    </div>
                    <div class="collapse navbar-collapse">
                        <ul class="nav navbar-nav">
                            <li class="active">
                                <a href="#">
                                    Home
                                </a>
                            </li>
                            <li>
                                <a href="#about">
                                    About
                                </a>
                            </li>
                            <li>
                                <a href="#contact">
                                    Contact
                                </a>
                            </li>
                        </ul>
                    </div>
                </div>
            </div>
            <div class="container">
                <div style="padding: 40px 15px; text-align: center;">
                    <h1>
                        Bootstrap starter template
                    </h1>
                    <p class="lead">
                        Use this document as a way to quickly start any new project
                        <br />
                        All you get is this text and a mostly barebones HTML document.
                    </p>
                </div>
            </div>
            <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js">
            </script>
            <script src="https://maxcdn.boostrapcdn.com/bootstrap/3.2.0/js/boostrap.min.js">
            </script>
        </body>
    </html>

