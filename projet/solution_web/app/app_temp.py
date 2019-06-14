from flask import Flask, make_response, render_template, request, send_file, flash
#from werkzeug import secure_filename
import json
import os

#from OpenSSL import SSL
#context = SSL.Context(SSL.PROTOCOL_TLSv1_2)
#context.use_privatekey_file('boudeville.key')
#context.use_certificate_file('boudeville.crt')



DOSSIER_SAVE = "/imagesUpload/"

app = Flask(__name__)
app.secret_key = 'd66HR8dgjYYic*dhfdsfsdf'


@app.route('/', methods=['GET', 'POST'])
def accueil():
    results = None
    if request.method == "POST":
        f = request.files['fic']
        if f:  # on vérifie qu'un fichier a bien été envoye
            f.save(DOSSIER_SAVE + f.filename)
            flash("Fichier bien sauvegarde")

            #lancer analyse ML
            results = {}
            results["models"] = []
            results["models"].append({"nom": "Modele lineaire", "implement": "NA", "framework": "NA"})
            results["models"].append({"nom": "PMC", "implement": "NA", "framework": "NA"})
            results["models"].append({"nom": "RBF", "implement": "NA", "framework": "NA"})
            print(results)

        else:
            flash("Vous avez oublié le fichier !")

    return render_template('accueil.html', data=results)


@app.errorhandler(404)
def page_non_trouvee(error):
    return  make_response("Cette page devrait vous avoir renvoyé une erreur 404", 404)


if __name__ == '__main__':

 #   app.run(host='0.0.0.0', port=80, ssl_context=context )
    app.run(host='0.0.0.0', port=80  )
  #  app.run(debug=True)

