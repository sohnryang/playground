from django.http import HttpResponse


def index(request):
    return HttpResponse(b"Hell world!")
