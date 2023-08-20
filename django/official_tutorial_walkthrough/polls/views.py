from django.http import HttpRequest, HttpResponse

from .models import Question


def index(request: HttpRequest) -> HttpResponse:
    latest_question_list = Question.objects.order_by("-pub_date")[:5]
    output = ", ".join([q.question_text for q in latest_question_list])
    return HttpResponse(output)


def detail(request: HttpRequest, question_id: int) -> HttpResponse:
    return HttpResponse(f"Question with id {question_id}.".encode())


def results(request: HttpRequest, question_id: int) -> HttpResponse:
    return HttpResponse(f"Results of question with id {question_id}".encode())


def vote(request: HttpRequest, question_id: int) -> HttpResponse:
    return HttpResponse(f"Voting on question with id {question_id}".encode())
