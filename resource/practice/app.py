from flask import Flask, render_template, request

# The (__name__) means to refer to current file's name nomatter what the file is named
# This line tells this framework to treat this code as a web application
app = Flask(__name__)

# @app.route("/") tells the browser what route (/) to find the index page. It calls index.html
@app.route("/", methods=["GET", "POST"])
def index():
    # This request.args.get returns a dictionary of key value pairs from the url, and returns either None or a SECOND ARGUMENT that you put in, if nothing is there
    # Render_template is the Flask function that sends the index.html file to server
    # Render_templates can take one or more arguments, the first argument is the one inside
    # the {{}} on the index.html doc, the second {=name) is the one defined above in this app.py page
    # name= part is a variable or placeholder {{ name }} on index.html, followed by value we pass in through the above code in this program name = request.args.get("name")
    if request.method == "POST":
        # Placeing files in the templates folder is important for program to work!
        return render_template("greet.html", name=request.form.get("name"))
    return render_template("index.html")


# Now we create a second @app.route("/greet") to handle the form just created in index.html
# methods= is an argment that gets passed into route and supports GET and POST, post erasing the info from the URL

