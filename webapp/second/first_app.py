from google.appengine.api import users
from google.appengine.ext import webapp
from google.appengine.ext.webapp.util import run_wsgi_app
providers = {
   'Google' : 'www.google.com/accounts/o8/id',
   'Yahoo' : 'yahoo.com',
   'MySpace' : 'myspace.com'
}

class Main(webapp.RequestHandler):
   def get(self):
      user = users.get_current_user()
      #are they signed in already?
      if user:
         self.response.out.write('Hello <em>%s</em>! [<a href="%s">Sign Out Here</a>]' % ( user.nickname(), users.create_logout_url(self.request.uri)))
      else:
         self.response.out.write('Hi! Please sign in at: ')
         for name, uri in providers.items():
            self.response.out.write('[<a href="%s">%s</a>]' % ( users.create_login_url(federated_identity=uri), name))
            
application = webapp.WSGIApplication([('/', Main)], debug=True)

def main():
   run_wsgi_app(application)

if __name__ == '__main__':
   main()


